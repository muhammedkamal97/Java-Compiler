//
// Created by mario_hunter on 4/19/19.
//

#include "LL1GrammarManufacturer.h"

LL1GrammarManufacturer::LL1GrammarManufacturer(ProductionRules *productions) : productions(productions) {}

map<string, vector<string> *> *
LL1GrammarManufacturer::getProductions() const {
    return productions;
}
