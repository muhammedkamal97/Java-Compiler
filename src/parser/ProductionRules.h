//
// Created by mostafa on 19/04/19.
//

#ifndef COMPILER_PRODUCTIONRULES_H
#define COMPILER_PRODUCTIONRULES_H


#include <set>
#include <map>
#include "Production.h"

struct ProductionRules{
    set<string>* non_terminals;
    map<string, int>  *production_rules_indexes;
    Production **production_rules;
};
#endif //COMPILER_PRODUCTIONRULES_H
