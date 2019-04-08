//
// Created by mario_hunter on 3/20/19.
//

#ifndef PROJECT_TOKEN_H
#define PROJECT_TOKEN_H

#include<map>
#include <string>
#include "TokenType.h"

using namespace std;

struct Token {
    TokenType* type;
    string lexeme;
    map<string, void *> *attr;

    Token(TokenType *type, const string &lexeme) : type(type), lexeme(lexeme) {}
};


#endif //PROJECT_TOKEN_H
