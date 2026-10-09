#include <iostream>
#include <vector>
#include <string>

#include "reader.h"
#include "solver.h"
#include "state.h"

using namespace std;

bool ReadOptions(
    int argc,
    char* argv[],
    string& configFile,
    string& inputFile,
    bool& doTrace
) {
    bool hasConfigFile = false;
    bool hasInputFile = false;
    bool hasTraceOption = false;

    for (int i = 1; i < argc; ++i) {
        string argument = argv[i];

        if (argument[0] != '-') {
            cerr << "Argumento desconocido: " << argument << endl;
            return false;
        }

        switch (argument[1]) {
            case 'c':
                if (argument != "-config" || i + 1 >= argc) {
                    cerr << "Argumento inválido: " << argument << endl;
                    return false;
                }

                configFile = argv[++i];
                hasConfigFile = true;
                break;

            case 't': {
                if (argument != "-trace" || i + 1 >= argc) {
                    cerr << "Argumento inválido: " << argument << endl;
                    return false;
                }

                string traceOption = argv[++i];

                if (traceOption != "y" && traceOption != "n") {
                    cerr << "Error: -trace debe ser y o n." << endl;
                    return false;
                }

                doTrace = (traceOption == "y");
                hasTraceOption = true;
                break;
            }

            case 'i':
                if (argument != "-in" || i + 1 >= argc) {
                    cerr << "Argumento inválido: " << argument << endl;
                    return false;
                }

                inputFile = argv[++i];
                hasInputFile = true;
                break;

            default:
                cerr << "Argumento desconocido: " << argument << endl;
                return false;
        }
    }

    if (!hasConfigFile || !hasInputFile || !hasTraceOption) {
        cerr << "Uso: " << argv[0]
             << " -config <f> -trace <y|n> -in <f>"
             << endl;
        return false;
    }

    return true;
}

void PrintAutomaton(Automaton& automaton) {
    cout << "Estados:";
    for (const State& state : automaton.states) {
        cout << " " << state.GetName();
    }
    cout << endl;

    cout << "Símbolos de entrada:";
    for (const Symbol& symbol : automaton.inputSymbols) {
        cout << " " << symbol.GetName();
    }
    cout << endl;

    cout << "Símbolos de pila:";
    for (const Symbol& symbol : automaton.stackSymbols) {
        cout << " " << symbol.GetName();
    }
    cout << endl;

    cout << "Estado inicial: " << automaton.initialState.GetName() << endl;

    cout << "Símbolo inicial de pila: "
         << automaton.initialStackSymbols.front().GetName() << endl;

    cout << "Estados finales:";
    for (const State& state : automaton.finalStates) {
        cout << " " << state.GetName();
    }
    cout << endl;

    for (const Transition& transition : automaton.transitions) {
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
    string configFile;
    string inputFile;
    bool doTrace = false;

    if (!ReadOptions(argc, argv, configFile, inputFile, doTrace)) {
        return 1;
    }

    Reader reader(configFile, inputFile);

    if (!reader.ReadAutomaton()) {
        cerr << "Error al leer el archivo del autómata." << endl;
        return 1;
    }

    Automaton automaton = reader.GetAutomaton();

    if (doTrace) {
        PrintAutomaton(automaton);
    }

    vector<vector<Symbol>> inputSymbolsList;
    reader.ReadInputFile(automaton.inputSymbols, inputSymbolsList);

    Solver solver(automaton);

    for (const auto& symbols : inputSymbolsList) {
        bool accepted = solver.Solve(symbols, doTrace);

        cout << "Cadena: ";

        for (const Symbol& symbol : symbols) {
            cout << symbol.GetName();
        }

        cout << " -> " << (accepted ? "Aceptada" : "Rechazada") << endl;
    }

    return 0;
}