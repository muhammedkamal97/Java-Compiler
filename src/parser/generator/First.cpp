//
// Created by mario_hunter on 4/19/19.
//



#include "First.h"

map<string, vector<string> *> *
compute_first(ProductionRules *productions) {
    ProductionRules *p = productions;
    map<string,set<string>> first_sets;
    map<string,bool> dp;
    for(string non_terminal : *productions->non_terminals){
        dp[non_terminal] = false;
    }

    for(string non_terminal : *productions->non_terminals){
        first(&first_sets,non_terminal,p,&dp);
    }
    map<string,vector<string>*>* result = new map<string,vector<string>*>();

    for(auto it : first_sets){
        vector<string>* temp = new vector<string>();
        // ensure that epsilon(\\L) will always be at index 0
        // if it exists
        if(contain_epsilon(it.second)){
            temp->push_back("\\L");
            it.second.erase("\\L");
        }

        for(string st : it.second){
            temp->push_back(st);
        }

        (*result)[it.first] = temp;
    }
    return result;

}


void first(map<string,set<string>> *first_sets,string non_terminal,
        ProductionRules *productions,
        map<string,bool> *dp){

    int non_terminal_index = (*productions->production_rules_indexes)[non_terminal];
    Production non_terminal_productions =
                                     *((productions->production_rules)[non_terminal_index]);

    if((*dp)[non_terminal]){
        return;
    }
    (*dp)[non_terminal] = true;

    for(vector<GrammarSymbol *> * production : *non_terminal_productions.productions){
        for(GrammarSymbol* symbol : *production){
            string s = symbol->value;
            if(is_terminal(symbol->value,productions) && symbol->value != "\\L"){
                (*first_sets)[non_terminal].insert(symbol->value);
                if(contain_epsilon((*first_sets)[non_terminal])){
                    (*first_sets)[non_terminal].erase("\\L");
                }
                break;
            }else if(symbol->value == "\\L"){
                (*first_sets)[non_terminal].insert(symbol->value);
                break;
            }
            first(first_sets,symbol->value,productions,dp);
            for(string st : (*first_sets)[symbol->value]){
                (*first_sets)[non_terminal].insert(st);
            }
            if(!contain_epsilon((*first_sets)[symbol->value])){
                if(contain_epsilon((*first_sets)[non_terminal])){
                    (*first_sets)[non_terminal].erase("\\L");
                }
                break;
            }
        }
    }

    if(non_terminal_productions.has_epsilon){
        (*first_sets)[non_terminal].insert("\\L");
    }

}


bool is_terminal(string symbol,ProductionRules *productions){
    return productions->non_terminals->find(symbol) ==
            productions->non_terminals->end();
}

bool contain_epsilon(set<string> s){
    return s.find("\\L") != s.end();
}