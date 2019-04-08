//
// Created by mario_hunter on 3/20/19.
//

#include "Error.h"

Error::Error(string reporter_module, string error_msg, map<string, void *>* attr) : reporter_module(reporter_module),
        error_msg(error_msg), attr(attr) {}