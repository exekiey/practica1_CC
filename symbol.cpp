#include "symbol.h"
#include <string>

using namespace std;

Symbol Symbol::epsilon;

Symbol::Symbol(const std::string& name) : name(name) {}
Symbol::Symbol(){};
string Symbol::GetName() const { return name; }
bool Symbol::operator<(const Symbol& other) const {
    return name < other.name;
}
bool Symbol::operator==(const Symbol& other) const {
  return name == other.name;
}
bool Symbol::IsEpsilon() const {
  return *this == Symbol::epsilon;
}
void Symbol::SetEpsilon(const string& epsilonName) {
    epsilon = Symbol(epsilonName);
}
