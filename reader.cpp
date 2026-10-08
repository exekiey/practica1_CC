#include "reader.h"

using namespace std;

Reader::Reader(const string& automatonFilename, const string& inputFilename) :
    file(automatonFilename),
    inputFile(inputFilename),
    automaton(set<Symbol>(), set<Symbol>(), set<State>(), State(), vector<Symbol>(), set<State>(), set<Transition>()) {}

set<State> Reader::SplitStates(const string& line) {
	set<State> result;
	vector<string> tokens = SplitString(line, ' ');
	for (const string& token : tokens) {
		result.insert(State(token));
	}
	return result;
}

bool Reader::IsLineComment(const string& line) const {
	return line[0] == Reader::commentCharacter;;
}

bool Reader::SplitSymbols(const string& line, set<Symbol>& symbols) {
	vector<string> tokens = SplitString(line, ' ');
	for (const string& token : tokens) {
		if (token.size() != 1) {
			cerr << "Error: el símbolo '" << token << "' no es de un único carácter." << endl;
			return false;
		}
		if (token == epsilonSymbol) {
			cerr << "Error: el símbolo '" << epsilonSymbol << "' no es válido porque está reservado para representar ε" << endl;
			return false;
		}
		symbols.insert(Symbol(token));
	}
	return true;
}

bool Reader::IsSubset(const set<State>& a, const set<State>& b) const {
	for (const State& state : a) {
		if (b.find(state) == b.end()) return false;
	}
	return true;
}

bool Reader::Contains(const set<State>& values, const State& value) const {
	return values.find(value) != values.end();
}

bool Reader::Contains(const set<Symbol>& values, const Symbol& value) const {
	return values.find(value) != values.end();
}

bool Reader::ValidateTransition(const Transition& transition) {
	if (!Contains(automaton.states, transition.currentState)) {
		cerr << "Error: el estado origen '" << transition.currentState.GetName()
			<< "' no pertenece a Q." << endl;
		return false;
	}

	if (!Contains(automaton.states, transition.transitionedState)) {
		cerr << "Error: el estado destino '" << transition.transitionedState.GetName()
			<< "' no pertenece a Q." << endl;
		return false;
	}

	if (!Contains(automaton.inputSymbols, transition.inputSymbol) && !transition.inputSymbol.IsEpsilon()) {
		cerr << "Error: el símbolo de entrada '" << transition.inputSymbol.GetName()
			<< "' no pertenece a Σ." << endl;
		return false;
	}

	if (!Contains(automaton.stackSymbols, transition.stackTop)) {
		cerr << "Error: el símbolo de cima de pila '" << transition.stackTop.GetName()
			<< "' no pertenece a Γ." << endl;
		return false;
	}

	for (const Symbol& symbol : transition.addedSymbols) {
		if (!Contains(automaton.stackSymbols, symbol) && !symbol.IsEpsilon()) {
			cerr << "Error: el símbolo a apilar '" << symbol.GetName()
				<< "' no pertenece a Γ." << endl;
			return false;
		}
	}

	return true;
}

bool Reader::ReadAutomaton() {
	automaton = Automaton(std::set<Symbol>(), std::set<Symbol>(), std::set<State>(), State(), std::vector<Symbol>(), std::set<State>(), std::set<Transition>());

	Symbol::SetEpsilon(epsilonSymbol);

	if (!file.is_open()) {
		cerr << "Error: no se pudo abrir el fichero." << endl;
		return false;
	}

	string line;

	while (getline(file, line)) {
		if (!IsLineComment(line)) {
			break;
		}
	}
	
	automaton.states = SplitStates(line);
	if (automaton.states.empty()) {
		cerr << "Error: Q está vacío." << endl;
		cerr << "Línea: " << line << endl;
		return false;
	}

	if (!getline(file, line)) {
		cerr << "Error: falta la sección del alfabeto de entrada (Σ)." << endl;
		return false;
	}
	if (!SplitSymbols(line, automaton.inputSymbols)) {
		cerr << "Error: Σ contiene un símbolo que no es de un único carácter." << endl;
		cerr << "Línea: " << line << endl;
		return false;
	}

	if (!getline(file, line)) {
		cerr << "Error: falta la sección del alfabeto de pila (Γ)." << endl;
		return false;
	}
	if (!SplitSymbols(line, automaton.stackSymbols)) {
		cerr << "Error: Γ contiene un símbolo que no es de un único carácter." << endl;
		cerr << "Línea: " << line << endl;
		return false;
	}

	if (!getline(file, line)) {
		cerr << "Error: falta el estado inicial (q0)." << endl;
		return false;
	}
	automaton.initialState = State(line);
	if (!Contains(automaton.states, automaton.initialState)) {
		cerr << "Error: el estado inicial '" << automaton.initialState.GetName()
			<< "' no pertenece a Q." << endl;
		cerr << "Línea: " << line << endl;
		return false;
	}

	if (!getline(file, line)) {
		cerr << "Error: falta el símbolo inicial de pila (A0)." << endl;
		return false;
	}

	automaton.initialStackSymbols.push_back(Symbol(line));
	if (!Contains(automaton.stackSymbols, automaton.initialStackSymbols.back())) {
		cerr << "Error: el símbolo inicial de pila '" << automaton.initialStackSymbols.back().GetName()
			<< "' no pertenece a Γ." << endl;
		cerr << "Línea: " << line << endl;
		return false;
	}

	if (!getline(file, line)) {
		cerr << "Error: falta la sección de estados finales (F)." << endl;
		return false;
	}
	automaton.finalStates = SplitStates(line);
	if (!IsSubset(automaton.finalStates, automaton.states)) {
		cerr << "Error: F no es subconjunto de Q." << endl;
		cerr << "Línea: " << line << endl;
		return false;
	}

	int lineNumber = 7;
	while (getline(file, line)) {
		lineNumber++;
		if (line.empty()) continue;

		vector<string> tokens = SplitString(line, ' ');
		if (tokens.size() < 5) {
			cerr << "Error (línea " << lineNumber
				<< "): una transición debe tener 5 tokens." << endl;
			cerr << "Línea: " << line << endl;
			return false;
		}
		
		State currentState = State(tokens[0]);
		Symbol inputSymbol = Symbol(tokens[1]);
		Symbol stackTop = Symbol(tokens[2]);
		State nextState = State(tokens[3]);
		string addedSymbolsString = tokens[4];
		vector<string> splitAddedSymbols = SplitString(addedSymbolsString);
		vector<Symbol> addedSymbols;
		for (const string& currentChar : splitAddedSymbols) {
            Symbol currentSymbol = Symbol(currentChar);
            if (currentSymbol.IsEpsilon()) {
                continue;
            }
			addedSymbols.push_back(currentSymbol);
		}
		Transition currentTransition = {currentState, inputSymbol, stackTop, nextState, addedSymbols};

		if (!ValidateTransition(currentTransition)) {
			cerr << "Error (línea " << lineNumber
				<< "): transición inválida." << endl;
			cerr << "Línea: " << line << endl;
			return false;
		}
		automaton.transitions.insert(currentTransition);
	}

	return true;
}

bool Reader::ReadInputFile(const set<Symbol>& inputSymbols, vector<vector<Symbol>>& inputSymbolsList) {
    if (!inputFile.is_open()) {
        cerr << "Error: no se pudo abrir el fichero de entrada." << endl;
        return false;
    }

    string line;
    while (getline(inputFile, line)) {
        vector<string> tokens = SplitString(line);
        vector<Symbol> currentInputSymbols;
        for (const string& token : tokens) {
            Symbol symbol(token);
            if (!Contains(automaton.inputSymbols, symbol)) {
                cerr << "Error: el símbolo de entrada '" << symbol.GetName()
                    << "' no pertenece a Σ." << endl;
                cerr << "Línea: " << line << endl;
                return false;
            }
            currentInputSymbols.push_back(symbol);
        }
        inputSymbolsList.push_back(currentInputSymbols);
    }


    return true;
}

const Automaton Reader::GetAutomaton() const {
	return automaton;
}