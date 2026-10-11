#ifndef TRANSITION_H
#define TRANSITION_H

#include <vector>

#include "state.h"
#include "symbol.h"

struct Transition {
	State currentState;
	Symbol inputSymbol;
	Symbol stackTop;
	State transitionedState;
	std::vector<Symbol> addedSymbols;

	bool operator<(const Transition& other) const;
    bool MatchEpsilon(Symbol stackSymbol, State currentState) const;
    bool Match(Symbol inputSymbol, Symbol stackSymbol, State currentState) const;
};

#endif