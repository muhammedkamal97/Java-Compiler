//
// Created by mario_hunter on 3/19/19.
//

#ifndef PROJECT_NFAMANIFACTURER_H
#define PROJECT_NFAMANIFACTURER_H

#include<map>
#include <vector>
#include <string>
#include <set>

using namespace std;

class NFAManufacturer {
private:
    map<char, int> *input_map;
    vector<set<int>[]> *transition_diagram;
public:
    NFAManufacturer(map<string, vector<string>> rules);

    void generate_diagram();


    map<char, int> *getInput_map() const {
        return input_map;
    }

    vector<set<int>[]> *getTranisition_diagram() const {
        return transition_diagram;
    }

};


#endif //PROJECT_NFAMANIFACTURER_H
