#ifndef SOLVER_H
#define SOLVER_H

#include <queue>
#include <stack>
#include <vector>

#include "automaton.h"
#include "node.h"
#include "state.h"
#include "symbol.h"
#include "transition.h"

struct StateAndAddedSymbols {
    State state;
    std::vector<Symbol> addedSymbols;

    StateAndAddedSymbols(State state, std::vector<Symbol> addedSymbols);
};

class Solver {
private:
    Automaton automaton;

    bool Contains(const std::set<State>& values, const State& value) const;

    std::vector<StateAndAddedSymbols> GetNextStates(
        const State& currentState,
        const Symbol& inputSymbol,
        const Symbol& stackSymbol
    ) const;

    void AppendVectorToStack(
        std::stack<Symbol>& stack,
        const std::vector<Symbol>& symbols
    );
    void PrintNode(const Node& node, const std::vector<Symbol>& input, const Automaton& automaton);

public:
    Solver(const Automaton& automaton);

    bool Solve(const std::vector<Symbol>& input, bool doTrace);
    void GenerateEpsilonNodes(Node& currentNode, std::queue<Node>& BFSqueue);
};

#endif