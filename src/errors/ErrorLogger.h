//
// Created by mario_hunter on 3/20/19.
//

#ifndef PROJECT_ERRORLOGGER_H
#define PROJECT_ERRORLOGGER_H


#include <vector>
#include "Error.h"

using namespace std;

class ErrorLogger {
private:
    vector<Error> errors;
public:
    void report(string reporter, string error_msg, map<string, void *> *attr = nullptr);

    void report(Error *error);
};


#endif //PROJECT_ERRORLOGGER_H
