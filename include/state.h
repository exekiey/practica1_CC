#ifndef STATE_H
#define STATE_H

#include <string>
#include <iostream>

using namespace std;

class State {
private:
    string name;

public:
    State(const string& name);
    State();
    bool operator<(const State& other) const;
    string GetName() const;
    bool operator==(const State& other) const;
};

#endif