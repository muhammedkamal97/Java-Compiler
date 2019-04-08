//
// Created by mostafa on 25/03/19.
//

#ifndef COMPILER_TOKENTYPE_H
#define COMPILER_TOKENTYPE_H

#include <string>

using namespace std;

struct TokenType {
    string name;
    bool has_symbol_table_entry;

    TokenType(const string &name, bool has_symbol_table_entry=false) : name(name), has_symbol_table_entry(
            has_symbol_table_entry) {}
};



#endif //COMPILER_TOKENTYPE_H
