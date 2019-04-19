//
// Created by mario_hunter on 4/19/19.
//

#ifndef PROJECT_PDTMANUFACTURER_H
#define PROJECT_PDTMANUFACTURER_H

#include <boost/algorithm/string.hpp>
#include <vector>
#include <map>
#include <tokens/TokenType.h>
#include <parser/ProductionRules.h>

using namespace std;

class PDTManufacturer {
private:
    ProductionRules *productions;
    map<string, vector<string> *> *first;
    map<string, vector<string> *> *follow;
    string **pdt;
    map<string, int> *non_terminal_map;
    map<string, int> *terminal_map;
    vector<string> *terminals;

public:
    PDTManufacturer(ProductionRules *productions, vector<string> * terminals);

    string **getPdt() const;

    map<string, int> *getNon_terminal_map() const;

    map<string, int> *getTerminal_map() const;


};


#endif //PROJECT_PDTMANUFACTURER_H
