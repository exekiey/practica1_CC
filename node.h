#ifndef NODE_H
#define NODE_H

#include "state.h"
#include "symbol.h"
#include "transition.h"
#include <vector>
#include <string>
#include <stack>

struct Node {
    State state;
    std::stack<Symbol> stack;
    std::vector<Symbol> input;
    int inputCounter;

    Node(State state, std::stack<Symbol> stack, int inputCounter);
};

#endif