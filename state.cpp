#include "state.h"


State::State(const string& name) {
	this->name = name;
}

State::State(){};

bool State::operator<(const State& other) const {
	return name < other.name;
}

string State::GetName() const {
	return name;
}

bool State::operator==(const State& other) const {
	return name == other.name;
}