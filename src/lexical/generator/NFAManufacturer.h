//
// Created by mario_hunter on 3/19/19.
//

#ifndef PROJECT_NFAMANIFACTURER_H
#define PROJECT_NFAMANIFACTURER_H

#include<map>
#include <vector>
#include <string>
#include <set>
#include <bits/stdc++.h>
#include "NFA.h"

using namespace std;

class NFAManufacturer {
private:
    map<char, int> *input_map;
    vector<set<int>[]> *transition_array;
    map<string,NFA*> definitions;
    map<string,NFA*> patterns;

    bool is_definition(string def);
    bool is_operator(string str);
    int operator_priority(char c);
    bool check_range(int i, vector<string> temp);

public:
    NFAManufacturer(map<string, vector<string>> rules);

    void generate_diagram();

    vector<string> regex_to_postfix(vector<string> expression);
    NFA* evaluate_postfix(vector<string> postfix);
    map<char, int> *getInput_map() const {
        return input_map;
    }

    vector<set<int>[]> *getTranisition_array() const {
        return transition_array;
    }

};


#endif //PROJECT_NFAMANIFACTURER_H
