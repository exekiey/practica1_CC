#include "solver.h"

Solver::Solver(const Automaton& automaton)
    : automaton(automaton) {
}

bool Solver::Contains(
    const std::set<State>& values,
    const State& value
) const {
    for (const State& state : values) {
        if (state == value) {
            return true;
        }
    }

    return false;
}

void Solver::PrintNode(const Node& node, const std::vector<Symbol>& input, const Automaton& automaton) {
    std::cout << "Estado: " << node.state.GetName() << std::endl;

    std::cout << "Input: ";
    for (int i = node.inputCounter; i < input.size(); ++i) {
        std::cout << input[i].GetName();
    }
    std::cout << endl;
    std::cout << "Stack: [";

    std::stack<Symbol> stackCopy = node.stack;
    while (!stackCopy.empty()) {
        Symbol symbol = stackCopy.top();
        stackCopy.pop();
        std::cout << symbol.GetName();
        if (!stackCopy.empty()) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
    std::cout << "Transiciones posibles: ";
    if (node.stack.empty()) {
        std::cout << endl;
        return;
    }
    std::cout << endl;
    for (const Transition& transition : automaton.transitions) {
        bool endOfInput = node.inputCounter == input.size();
        if (transition.MatchEpsilon(node.stack.top(), node.state)
            || (!endOfInput && transition.Match(input[node.inputCounter], node.stack.top(), node.state))) {
            std::cout << "(" << transition.currentState.GetName() << ", "
                << transition.inputSymbol.GetName() << ", "
                << transition.stackTop.GetName() << ") -> ("
                << transition.transitionedState.GetName() << ", [";
            for (const Symbol& symbol : transition.addedSymbols) {
                std::cout << symbol.GetName();
            }
            std::cout << "])";
            if (&transition != &(*automaton.transitions.rbegin())) {
                std::cout << ", ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << endl;
}

void Solver::GenerateEpsilonNodes(Node& currentNode, std::queue<Node>& BFSqueue) {
    for (const Transition& transition : automaton.transitions) {
        State transitionedState;
        std::vector<Symbol> addedSymbols;

        if (transition.MatchEpsilon(currentNode.stack.top(), currentNode.state)) {
            std::stack<Symbol> stackCopy = currentNode.stack;
            stackCopy.pop();

            AppendVectorToStack(
                stackCopy,
                transition.addedSymbols
            );

            Node newNode(
                transition.transitionedState,
                stackCopy,
                currentNode.inputCounter
            );
            BFSqueue.push(newNode);
        }
    }
}

void Solver::AppendVectorToStack(
    std::stack<Symbol>& stack,
    const std::vector<Symbol>& symbols
) {
    for (auto it = symbols.rbegin(); it != symbols.rend(); ++it) {
        stack.push(*it);
    }
}

bool Solver::Solve(const std::vector<Symbol>& input, bool doTrace) {
    

    std::queue<Node> BFSqueue = std::queue<Node>();
    std::stack<Symbol> initialStack;

    AppendVectorToStack(
        initialStack,
        automaton.initialStackSymbols
    );

    BFSqueue.push(
        Node(
            automaton.initialState,
            initialStack,
            0
        )
    );

    while (!BFSqueue.empty()) {
        Node currentNode = BFSqueue.front();
        BFSqueue.pop();
        if (doTrace) {
            PrintNode(currentNode, input, automaton);
        }
        int inputCounter = currentNode.inputCounter;
        std::stack<Symbol> stack = currentNode.stack;

        if (stack.empty()) {
            continue;
        }
        
        if (inputCounter == input.size()) {
            if (Contains(automaton.finalStates, currentNode.state)) {
                return true;
            }
            GenerateEpsilonNodes(currentNode, BFSqueue);
            continue;
        }

        Symbol currentInputSymbol = input[inputCounter];

        Symbol currentStackSymbol = stack.top();

        for (const Transition& transition : automaton.transitions) {

            if (transition.Match(currentInputSymbol, currentStackSymbol, currentNode.state)) {
                std::stack<Symbol> stackCopy = stack;
                stackCopy.pop();

                AppendVectorToStack(
                    stackCopy,
                    transition.addedSymbols
                );

                Node newNode(
                    transition.transitionedState,
                    stackCopy,
                    inputCounter + 1
                );
                BFSqueue.push(newNode);
            }
            if (transition.MatchEpsilon(currentStackSymbol, currentNode.state)) {
                std::stack<Symbol> stackCopy = stack;
                stackCopy.pop();

                AppendVectorToStack(
                    stackCopy,
                    transition.addedSymbols
                );

                Node newNode(
                    transition.transitionedState,
                    stackCopy,
                    inputCounter
                );
                BFSqueue.push(newNode);
            }
        }
    }

    return false;
}