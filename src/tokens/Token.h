//
// Created by mario_hunter on 3/20/19.
//

#ifndef PROJECT_TOKEN_H
#define PROJECT_TOKEN_H

#include<map>
#include <string>

using namespace std;

struct Token {
    string name;
    string lexeme;
    map<string, void *> *attr;
};


#endif //PROJECT_TOKEN_H
