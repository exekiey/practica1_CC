#include "transition.h"

bool Transition::operator<(const Transition& other) const {
  if (currentState < other.currentState) return true;
  if (other.currentState < currentState) return false;

  if (inputSymbol < other.inputSymbol) return true;
  if (other.inputSymbol < inputSymbol) return false;

  if (stackTop < other.stackTop) return true;
  if (other.stackTop < stackTop) return false;

  if (transitionedState < other.transitionedState) return true;
  if (other.transitionedState < transitionedState) return false;

  return addedSymbols < other.addedSymbols;
}

bool Transition::MatchEpsilon(Symbol stackSymbol, State currentState) const {
    if ((this->stackTop == stackSymbol) &&
        (this->currentState == currentState) &&
        (this->inputSymbol.IsEpsilon())) {
        return true;
    }
    return false;
}

bool Transition::Match(Symbol inputSymbol, Symbol stackSymbol, State currentState) const {
    if ((this->inputSymbol == inputSymbol) &&
        (this->stackTop == stackSymbol) &&
        (this->currentState == currentState)) {
        return true;
    }
    return false;
}