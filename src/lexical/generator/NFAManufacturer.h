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
    vector<set<int>*> *transition_array;
    map<string,vector<string>> definitions;
    map<string,NFA*> patterns;
    //-------------------------------
    vector<string> punctuations;
    vector<pair<string,vector<string>>> expressions;
    vector<pair<string,vector<string>>> defination;
    vector<string> key_words;
    //---------------------------------
    bool is_definition(string def);
    bool is_operator(string str);
    bool unary_operator(string op);
    int operator_priority(char c);
    bool check_range(int i, vector<string> temp);
    void NFAManufacturers(vector<pair<string,vector<string>>> expressions,
    vector<pair<string,vector<string>>> definations,
    vector<string> key_words,
            vector<string> punctuations);
public:
    NFAManufacturer(vector<pair<string,vector<string>>> expressions,
            vector<pair<string,vector<string>>> definations,
                    vector<string> key_words,
                    vector<string> punctuations){
        this->punctuations = punctuations;
        this->expressions = expressions;
        this->defination = definations;
        this->key_words = key_words;
        NFAManufacturers(this->expressions,this->defination, this->key_words, this->punctuations);
    }

    void generate_diagram();

    vector<string> regex_to_postfix(vector<string> expression);
    NFA* evaluate_postfix(vector<string> postfix);
    map<char, int> *getInput_map() const {
        return input_map;
    }

    vector<set<int>*> *getTranisition_array() const {
        return transition_array;
    }

    NFA *nfa;
    vector<TokenType *> *tokens_vec;
    vector<vector<set<int>>> transition_table;
};


#endif //PROJECT_NFAMANIFACTURER_H
