//
// Created by mario_hunter on 4/19/19.
//

#ifndef PROJECT_FIRST_H
#define PROJECT_FIRST_H

#endif //PROJECT_FIRST_H

#include <boost/algorithm/string.hpp>
#include <vector>
#include <map>
#include <parser/ProductionRules.h>

using namespace std;

map<string, vector<string> *> *
compute_first(ProductionRules *productions);

bool
is_terminal(string symbol,ProductionRules *productions);

bool
contain_epsilon(set<string> s);

void
first(map<string,set<string>> *first_sets,string non_terminal,
           ProductionRules *productions,
            map<string,bool> *dp);