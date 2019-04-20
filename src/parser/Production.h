//
// Created by mostafa on 19/04/19.
//

#ifndef COMPILER_PRODUCTION_H
#define COMPILER_PRODUCTION_H

#include <string>
#include <vector>

using namespace std;


enum symbol_type {
    Terminal, NonTerminal
};

struct GrammarSymbol{
    string  value;
    symbol_type type;
    bool is_epsilon = false;

};

struct Production {
    GrammarSymbol* name;
    bool has_epsilon;
    bool is_start_production;
    bool is_sync = false;
    vector <vector< GrammarSymbol * > *> *productions;
};


#endif //COMPILER_PRODUCTION_H
