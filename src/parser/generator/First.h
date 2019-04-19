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
