//
// Created by mario_hunter on 4/9/19.
//

#ifndef PROJECT_COMPILER_H
#define PROJECT_COMPILER_H

#include <fstream>
#include <tables/SimpleSymbolTable.h>
#include "Component.h"

using namespace std;

class Compiler {
    SimpleSymbolTable *table;
public:
    Compiler();
    void compile(fstream * input);
};


#endif //PROJECT_COMPILER_H
