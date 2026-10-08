#include <iostream>
#include <vector>

#include "reader.h"
#include "solver.h"
#include "state.h"

using namespace std;

void PrintAutomaton(Automaton& automaton) {
  cout << "Estados:";
  set<State> states = automaton.states;
  for (const State& state : states) {
    cout << " " << state.GetName();
  }
  cout << endl;

  cout << "Símbolos de entrada:";
  set<Symbol> inputSymbols = automaton.inputSymbols;
  for (const Symbol& symbol : inputSymbols) {
    cout << " " << symbol.GetName();
  }
  cout << endl;

  cout << "Símbolos de pila:";
  set<Symbol> stackSymbols = automaton.stackSymbols;
  for (const Symbol& symbol : stackSymbols) {
    cout << " " << symbol.GetName();
  }
  cout << endl;

  State initialState = automaton.initialState;
  cout << "Estado inicial: " << initialState.GetName() << endl;

  Symbol initialStackSymbol = automaton.initialStackSymbols.front();
  cout << "Símbolo inicial de pila: " << initialStackSymbol.GetName() << endl;

  cout << "Estados finales:";
  set<State> finalStates = automaton.finalStates;
  for (const State& state : finalStates) {
    cout << " " << state.GetName();
  }
  cout << endl;

  set<Transition> transitions = automaton.transitions;
  for (const Transition& transition : transitions) {
    cout << "Transición: (" << transition.currentState.GetName() << ", "
         << transition.inputSymbol.GetName() << ", "
         << transition.stackTop.GetName() << ") -> ("
         << transition.transitionedState.GetName() << ", [";
    for (const Symbol& symbol : transition.addedSymbols) {
      cout << symbol.GetName();
    }
    cout << "])" << endl;
  }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Uso: " << argv[0] << " <archivo_automata> <trace> <archivo_entrada> " << endl;
        return 1;
    }
	Reader reader = Reader(argv[1], argv[3]);
    bool doTrace = (string(argv[2]) == "y");

	if (!reader.ReadAutomaton()) {
        cerr << "Error al leer el archivo del automata." << endl;
        return 1;
    }
    Automaton automaton = reader.GetAutomaton();

    if (doTrace) {
        PrintAutomaton(automaton);
    }

    vector<vector<Symbol>> inputSymbolsList;
    reader.ReadInputFile(automaton.inputSymbols, inputSymbolsList);

    Solver solver = Solver(automaton);

    for (const auto& symbols : inputSymbolsList) {
        bool accepted = solver.Solve(symbols, doTrace);
        cout << "Cadena: ";
        for (const Symbol& symbol : symbols) {
            cout << symbol.GetName();
        }
        cout << " -> " << (accepted ? "Aceptada" : "Rechazada") << endl;
    }
}