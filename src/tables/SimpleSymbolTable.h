//
// Created by mario_hunter on 4/9/19.
//

#ifndef PROJECT_SIMPLESYMBOLTABLE_H
#define PROJECT_SIMPLESYMBOLTABLE_H

#include <map>
using namespace std;

class SimpleSymbolTable {

public:
    SimpleSymbolTable();

    map<string,void*>* table;
};


#endif //PROJECT_SIMPLESYMBOLTABLE_H
