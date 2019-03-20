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
    vector<int[]> *transition_diagram;

public:
    DFAManufacturer(vector<set<int>[]> *transition_diagram);

    void generate_dfa();

    vector<int[]> *getTransition_diagram() const {
        return transition_diagram;
    }
};


#endif //PROJECT_DFAMANUFACTURER_H
