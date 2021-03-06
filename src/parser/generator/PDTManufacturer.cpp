//
// Created by mario_hunter on 4/19/19.
//

#include "Production.h"
#include "PDTManufacturer.h"
#include "First.h"
#include "Follow.h"


PDTManufacturer::PDTManufacturer(ProductionRules *production_rules,vector<string> * terminals) {
    this->production_rules = production_rules;
    this->first = compute_first(this->production_rules);
    this->follow = compute_follow(this->production_rules);
    this->terminals = terminals;
    vector<string> temp(production_rules->non_terminals->begin(),
                        production_rules->non_terminals->end());
    this->non_terminals = temp;
    this->non_terminal_map = new unordered_map<string, int>();
    this->terminal_map = new unordered_map<string, int>();
    createPDT();
}


void PDTManufacturer::createPDT(){
    constructNonTerminalMap();
    constructTerminalMap();
    initPDTTable();
    fillPDT();
}

void PDTManufacturer::constructNonTerminalMap(){
    for(int i = 0; i < non_terminals.size(); i++){
        non_terminal_map->insert({non_terminals[i],i});
    }
}

void PDTManufacturer::constructTerminalMap(){
    for(int i = 0; i < terminals->size(); i++){
        terminal_map->insert({(*terminals)[i],i});
    }
}

void PDTManufacturer::initPDTTable(){
    int rows = production_rules->non_terminals->size();
    int cols = terminals->size()+1;
    pdt = new Production **[rows];
    for(int i = 0; i < rows; i++){
        pdt[i] = new Production*[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            pdt[i][j] = NULL;
        }
    }
}


void PDTManufacturer::fillPDT(){
    for(int i = 0; i < non_terminals.size(); i++){
        int non_terminal_index = production_rules->production_rules_indexes->at(non_terminals[i]);
        fillPDTRow(i, non_terminal_index);
    }
}


void PDTManufacturer::fillPDTRow(int row, int non_terminal_index){
    bool is_follow_slots_filled = false;
    vector <vector< GrammarSymbol * > *> *single_production = production_rules->production_rules[non_terminal_index]->productions;
    string non_terminal = production_rules->production_rules[non_terminal_index]->name->value;
    for(int j = 0; j < single_production->size(); j++){
        string symbol = (*single_production)[j]->at(0)->value;
        if(terminal_map->find(symbol) != terminal_map->end()){
            Production *production = getProduction(non_terminal_index, j, single_production, false, false);
            pdt[row][terminal_map->find(symbol)->second] = production;
        }else{
            addFirstTerminals(symbol, row, j,non_terminal_index, single_production);
        }
        if((containsEpsilon(first->find(symbol)->second))){
            is_follow_slots_filled = true;
            addFollowTerminals(non_terminal, row, non_terminal_index, j, single_production, false);
        }
    }
    if(production_rules->production_rules[non_terminal_index]->has_epsilon){
        addFollowTerminals(non_terminal, row, non_terminal_index, 0, single_production, true);
        is_follow_slots_filled = true;
    }
    if(!is_follow_slots_filled) {
        addSyncSlots(non_terminal, row, non_terminal_index, 0, single_production);
    }
}


void PDTManufacturer::addSyncSlots(string symbol, int row, int non_terminal_index, int grammer_symbol_vector_index, vector <vector< GrammarSymbol * > *> *single_production){
    vector<string> *follow_terminals = follow->find(symbol)->second;
    for(int k = 0; k < follow_terminals->size(); k++){
        Production *production = getProduction(non_terminal_index, grammer_symbol_vector_index, single_production, false, true);
        if((*follow_terminals)[k].compare("$") == 0){
            pdt[row][terminal_map->size()] = production;
        } else{
            pdt[row][terminal_map->find((*follow_terminals)[k])->second] = production;
        }
    }
}
Production *PDTManufacturer::getProduction(int non_terminal_index, int grammer_symbol_vector_index, vector <vector< GrammarSymbol * > *> *productions, bool epsilon, bool is_sync){
    Production *old_production =  (production_rules->production_rules[non_terminal_index]);
    Production *new_production = cloneProduction(old_production);
    if(epsilon) {
        new_production->has_epsilon = true;

    }else if (is_sync){
        new_production->is_sync = true;
        new_production->has_epsilon = false;

    }else{
        vector<vector<GrammarSymbol *> *> *production_vector = new vector<vector<GrammarSymbol *> *>();
        vector<GrammarSymbol *> *grammerSymbols = (*productions)[grammer_symbol_vector_index];
        production_vector->push_back(grammerSymbols);
        new_production->productions = production_vector;
        new_production->has_epsilon = false;
    }
    return new_production;
}

Production *PDTManufacturer::cloneProduction(Production *old_production){
    Production *new_production = new Production();
    new_production->has_epsilon = old_production->has_epsilon;
    new_production->is_start_production = old_production->is_start_production;
    new_production->name = old_production->name;
    new_production->is_sync = old_production->is_sync;
    return new_production;
}

void PDTManufacturer::addFirstTerminals(string symbol, int row, int grammer_symbol_vector_index,int non_terminal_index, vector <vector< GrammarSymbol * > *> *single_production){
    vector<string> *first_terminals = first->find(symbol)->second;
    int k;
    if(containsEpsilon(first->find(symbol)->second)){
        k = 1;
    } else{
        k = 0;
    }
    for( ;k < first_terminals->size(); k++){
        Production *production = getProduction(non_terminal_index, grammer_symbol_vector_index, single_production, false, false);
        pdt[row][terminal_map->find((*first_terminals)[k])->second] = production;
    }
}

void PDTManufacturer::addFollowTerminals(string symbol, int row, int non_terminal_index, int grammer_symbol_vector_index, vector <vector< GrammarSymbol * > *> *single_production, bool epsilon){
    vector<string> *follow_terminals = follow->find(symbol)->second;

    for(int k = 0; k < follow_terminals->size(); k++){
        if((*follow_terminals)[k].compare("$") == 0){
            Production *production = getProduction(non_terminal_index, grammer_symbol_vector_index, single_production, epsilon, false);
            pdt[row][terminals->size()] = production;
        } else{
            Production *production = getProduction(non_terminal_index, grammer_symbol_vector_index, single_production, epsilon, false);
            pdt[row][terminal_map->find((*follow_terminals)[k])->second] = production;
        }
    }

}


bool PDTManufacturer::containsEpsilon(vector<string> *first_terminals){
    if ((*first_terminals)[0].compare("\\L") == 0){
        return true;
    }
    return false;
}

Production ***
PDTManufacturer::getPdt() const {
    return pdt;
}

unordered_map<string, int> *
PDTManufacturer::getNon_terminal_map() const {
    return non_terminal_map;
}

unordered_map<string, int> *
PDTManufacturer::getTerminal_map() const {
    return terminal_map;
}

