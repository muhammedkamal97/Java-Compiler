//
// Created by mario_hunter on 4/19/19.
//



#include "First.h"

map<string, vector<string> *> *
compute_first(ProductionRules *productions) {
    ProductionRules *p = productions;
    map<string,set<string>> first_sets;
    for(string non_terminal : *productions->non_terminals){
        first(&first_sets,non_terminal,p);
    }
    map<string,vector<string>*>* result = new map<string,vector<string>*>();

    for(auto it : first_sets){
        vector<string>* temp = new vector<string>();
        for(string st : it.second){
            temp->push_back(st);
        }
        (*result)[it.first] = temp;
    }
    return result;

}


void first(map<string,set<string>> *first_sets,string non_terminal,
        ProductionRules *productions){

    int non_terminal_index = (*productions->production_rules_indexes)[non_terminal];
    Production non_terminal_productions =
                                     *(*(productions->production_rules) + non_terminal_index);

    for(vector<string> * production : non_terminal_productions.productions){
        for(string symbol : *production){
            string s = symbol;
            if(is_terminal(symbol,productions) && symbol != "\\L"){
                (*first_sets)[non_terminal].insert(symbol);
                break;
            }else if(symbol == "\\L"){
                (*first_sets)[non_terminal].insert(symbol);
                break;
            }
            first(first_sets,symbol,productions);
            for(string st : (*first_sets)[symbol]){
                (*first_sets)[non_terminal].insert(st);
            }
            if(!contain_epsilon((*first_sets)[symbol])){
                break;
            }
        }
    }

}


bool is_terminal(string symbol,ProductionRules *productions){
    return productions->non_terminals->find(symbol) ==
            productions->non_terminals->end();
}

bool contain_epsilon(set<string> s){
    return s.find("\\L") != s.end();
}