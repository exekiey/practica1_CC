#include "state.h"
#include "symbol.h"
#include "transition.h"
#include <vector>
#include <string>
#include <queue>
#include "node.h"
#include <stack>

Node::Node(State state, std::stack<Symbol> stack, int inputCounter)
    : state(state), stack(stack), inputCounter(inputCounter) {}