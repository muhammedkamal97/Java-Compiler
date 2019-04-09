//
// Created by mario_hunter on 3/20/19.
//

#include <iostream>
#include "ErrorLogger.h"

void ErrorLogger::report(Error *error) {
    std::cout << error->reporter_module << " Error: " << error->error_msg << endl;
}