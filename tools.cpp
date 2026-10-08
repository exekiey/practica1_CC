#include <string>
#include <vector>
#include "tools.h"
using namespace std;

vector<string> SplitString(const string& str, char delimiter) {
	vector<string> tokens;
	string token;
	for (char ch : str) {
		if (ch == delimiter) {
			tokens.push_back(token);
			token.clear();
			continue;
		}
		token += ch;
	}
	tokens.push_back(token);
	return tokens;
}

vector<string> SplitString(const string& str) {
	vector<string> tokens;
	for (char ch : str) {
		tokens.push_back(string(1, ch));
	}
	return tokens;
}