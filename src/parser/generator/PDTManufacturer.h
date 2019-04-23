//
// Created by mario_hunter on 4/19/19.
//

#ifndef PROJECT_PDTMANUFACTURER_H
#define PROJECT_PDTMANUFACTURER_H

#include <boost/algorithm/string.hpp>
#include <vector>
#include <map>

#include<string.h>
#include "parser/ProductionRules.h"
#include "parser/Production.h"
#include "unordered_map"

using namespace std;

class PDTManufacturer {
private:
    ProductionRules *production_rules;
    map<string, vector<string> *> *first;
    map<string, vector<string> *> *follow;
    Production ***pdt;
    unordered_map<string, int> *non_terminal_map;
    unordered_map<string, int> *terminal_map;
    vector<string> *terminals;
    vector<string> non_terminals;

    void initPDTTable();
    void fillPDT();
    bool containsEpsilon(vector<string> *first_terminals);
    void addFirstTerminals(string symbol, int row, int grammer_symbol_vector_table,int non_terminal_index, vector <vector< GrammarSymbol * > *> *single_production);
    void addFollowTerminals(string symbol, int row, int non_terminal_index, int grammer_symbol_vector_index, vector <vector< GrammarSymbol * > *> *single_production, bool epsilon);
    void fillPDTRow(int row, int non_terminal_index);
    void createPDT();
    void constructNonTerminalMap();
    void constructTerminalMap();
    Production *getProduction(int non_terminal_index, int grammer_symbol_vector_index, vector <vector< GrammarSymbol * > *> *productions, bool epsilon, bool is_sync);
    Production *cloneProduction(Production *old_production);
    void addSyncSlots(string symbol, int row, int non_terminal_index, int grammer_symbol_vector_index, vector <vector< GrammarSymbol * > *> *single_production);
    unordered_map<int, string> getReversedMap(unordered_map<string, int> *normal_map);
    vector<string> *clearTerminals(vector<string> *terminals);
public:
    PDTManufacturer(ProductionRules *production_rules, vector<string> * terminals);

    Production ***getPdt() const;
    unordered_map<string, int> *getNon_terminal_map() const;

    unordered_map<string, int> *getTerminal_map() const;
    void printPDT();


};


#endif //PROJECT_PDTMANUFACTURER_H