//
// Created by khaled on 4/8/19.
//

#include "ErrorRecoverer.h"
#include <fstream>

ErrorRecoverer::ErrorRecoverer(ErrorLogger *reporter, operation_mode mode) : reporter(reporter), mode(mode) {}

void ErrorRecoverer::recover(fstream *input, streamoff start_pos, int line, int line_pos, operation_mode mode) {
    input->clear();
    input->seekg(start_pos + 1);
    error_msg = "error in line " + to_string(line) + " at character " + to_string(line_pos);
}

void ErrorRecoverer::report() {
    Error* error = new Error("Lexical Analyzer", error_msg);
    reporter->report(error);
}