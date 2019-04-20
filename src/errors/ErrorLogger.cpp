//
// Created by mario_hunter on 3/20/19.
//

#include <iostream>
#include "ErrorLogger.h"

void ErrorLogger::report(Error *error) {
    errors->push_back(error);
    std::cout << error->reporter_module << " Error: " << error->error_msg << endl;
}

void
ErrorLogger::report(string reporter, string error_msg, map<string, void *> *attr) {
    Error *error =new Error(reporter,error_msg,attr);
    report(error);
}

ErrorLogger::ErrorLogger() {
    errors = new vector<Error*>();
}
