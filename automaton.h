#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "symbol.h"
#include "state.h"
#include "transition.h"

#include <set>
#include <vector>

struct Automaton {
    std::set<Symbol> inputSymbols;
    std::set<Symbol> stackSymbols;
    std::set<State> states;
    State initialState;
    std::vector<Symbol> initialStackSymbols;
    std::set<State> finalStates;
    std::set<Transition> transitions;

    Automaton(
        const std::set<Symbol>& inputSymbols,
        const std::set<Symbol>& stackSymbols,
        const std::set<State>& states,
        State initialState,
        const std::vector<Symbol>& initialStackSymbols,
        const std::set<State>& finalStates,
        const std::set<Transition>& transitions
    );
};

#endif