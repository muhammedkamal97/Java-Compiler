//
// Created by khaled on 4/22/19.
//

#include "ProductionRules.h"

ProductionRules::ProductionRules(vector<Production*>* productions_vector) {
    non_terminals = new set<string>;
    production_rules_indexes = new map<string, int>;
    size = productions_vector->size();
    production_rules = new Production*[size];

    for (int i = 0; i < size; i++) {
        Production* production = productions_vector->at(i);
        string lhs = production->name->value;
        non_terminals->insert(lhs);
        production_rules[i] = production;
        production_rules_indexes->insert(make_pair(lhs, i));
    }
}