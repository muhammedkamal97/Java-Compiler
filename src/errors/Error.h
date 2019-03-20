//
// Created by mario_hunter on 3/20/19.
//

#ifndef PROJECT_ERROR_H
#define PROJECT_ERROR_H

#include <string>
#include <map>

using namespace std;
struct Error {
    string reporter_module;
    string error_msg;
    map<string, void *> attr;

};


#endif //PROJECT_ERROR_H
