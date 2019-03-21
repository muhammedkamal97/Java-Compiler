//
// Created by mario_hunter on 3/19/19.
//

#ifndef PROJECT_DFAMANUFACTURER_H
#define PROJECT_DFAMANUFACTURER_H

#include<map>
#include <vector>
#include <string>
#include <set>

using namespace std;

class DFAManufacturer {
private:
    vector<int[]> *transition_array;

public:
    DFAManufacturer(vector<set<int>[]> *nfa_transition_array);

    void generate_dfa();

    vector<int[]> *getTransition_array() const {
        return transition_array;
    }
};


#endif //PROJECT_DFAMANUFACTURER_H
