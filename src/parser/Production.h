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

    GrammarSymbol(const string &value, symbol_type type, bool is_epsilon = false) : value(value), type(type),
                                                                            is_epsilon(is_epsilon) {}

};

struct Production {
    GrammarSymbol* name;
    bool has_epsilon;
    bool is_start_production;
    vector <vector< GrammarSymbol * > *> *productions;

    Production(GrammarSymbol *name, bool has_epsilon, bool is_start_production) : name(name), has_epsilon(has_epsilon),
                                                                                  is_start_production(
                                                                                          is_start_production) {
        productions = new vector <vector< GrammarSymbol * > *>;
    }
};


#endif //COMPILER_PRODUCTION_H
