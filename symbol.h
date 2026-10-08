#pragma once
#include <string>

using namespace std;

class Symbol {
private:
    std::string name;
    
    static Symbol epsilon;
public:
    Symbol(const string& name);
    Symbol();
    string GetName() const;
    bool operator<(const Symbol& other) const;
    bool operator==(const Symbol& other) const;
    bool IsEpsilon() const;
    static void SetEpsilon(const string& epsilonName);
};