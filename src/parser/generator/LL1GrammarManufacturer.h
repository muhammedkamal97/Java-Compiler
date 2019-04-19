//
// Created by mario_hunter on 4/19/19.
//

#ifndef PROJECT_LL1GRAMMARMANUFACTURER_H
#define PROJECT_LL1GRAMMARMANUFACTURER_H


#include <boost/algorithm/string.hpp>
#include <map>
#include <vector>

using namespace std;
class LL1GrammarManufacturer {
private:
    map<string,vector<string>*> * productions;
public:
    LL1GrammarManufacturer(map<string, vector<string> *> *productions);

    map<string, vector<string> *> *getProductions() const;
};


#endif //PROJECT_LL1GRAMMARMANUFACTURER_H
