//
// Created by mostafa on 19/04/19.
//

#ifndef COMPILER_PRODUCTION_H
#define COMPILER_PRODUCTION_H

#include <string>
#include <vector>

using namespace std;


struct Production {
    string name;
    bool has_epsilon;
    bool is_start_production;
    vector <vector< string > *> productions;
};
#endif //COMPILER_PRODUCTION_H
