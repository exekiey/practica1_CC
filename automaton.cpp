#include "automaton.h"

#include <set>
#include <vector>

Automaton::Automaton(
    const std::set<Symbol>& inputSymbols,
    const std::set<Symbol>& stackSymbols,
    const std::set<State>& states,
    State initialState,
    const std::vector<Symbol>& initialStackSymbols,
    const std::set<State>& finalStates,
    const std::set<Transition>& transitions
) :
    inputSymbols(inputSymbols),
    stackSymbols(stackSymbols),
    states(states),
    initialState(initialState),
    initialStackSymbols(initialStackSymbols),
    finalStates(finalStates),
    transitions(transitions) {}