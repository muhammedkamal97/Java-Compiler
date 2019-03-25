//
// Created by mario_hunter on 3/23/19.
//

#ifndef PROJECT_COMPARE_H
#define PROJECT_COMPARE_H

#include "gtest/gtest.h"
#include <vector>

using namespace std;

void
compare_dfas(vector<int *> *exp, vector<int *> *act);

void
compare_closures(set<int> **exp, set<int> **act);

#endif //PROJECT_COMPARE_H
