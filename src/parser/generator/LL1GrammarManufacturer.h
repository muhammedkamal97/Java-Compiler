//
// Created by mario_hunter on 4/19/19.
//

#ifndef PROJECT_LL1GRAMMARMANUFACTURER_H
#define PROJECT_LL1GRAMMARMANUFACTURER_H


#include <boost/algorithm/string.hpp>
#include <map>
#include <vector>
#include <parser/ProductionRules.h>

using namespace std;
class LL1GrammarManufacturer {
private:
    ProductionRules * productions;
public:
    LL1GrammarManufacturer(ProductionRules *productions);

    ProductionRules *getProductions() const;
};


#endif //PROJECT_LL1GRAMMARMANUFACTURER_H
