#ifndef READER_H
#define READER_H

#include <fstream>
#include <set>
#include <string>
#include <vector>

#include "state.h"
#include "symbol.h"
#include "tools.h"
#include "transition.h"
#include "automaton.h"

using namespace std;

class Reader {
private:
	string epsilonSymbol = ".";
    char commentCharacter = '#';
	ifstream file;
    ifstream inputFile;
    Automaton automaton;
    vector<Symbol> inputSymbols;

	set<State> SplitStates(const string& line);
	bool SplitSymbols(const string& line, set<Symbol>& symbols);
	bool IsSubset(const set<State>& a, const set<State>& b) const;
	bool Contains(const set<State>& values, const State& value) const;
	bool Contains(const set<Symbol>& values, const Symbol& value) const;
	bool ValidateTransition(const Transition& transition);
  bool IsLineComment(const string& line) const;

public:
	Reader(const string& automatonFilename, const string& inputFilename);
	bool ReadAutomaton();
    bool ReadInputFile(const set<Symbol>& inputSymbols, vector<vector<Symbol>>& inputSymbolsList);
	const Automaton GetAutomaton() const;
};

#endif