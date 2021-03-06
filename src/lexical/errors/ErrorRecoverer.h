//
// Created by mario_hunter on 3/20/19.
//

#ifndef PROJECT_ERRORRECOVERER_H
#define PROJECT_ERRORRECOVERER_H


#include "../../errors/ErrorLogger.h"
#include "lexical/analyzer/Tokenizer.h"

class ErrorRecoverer {
private:
    ErrorLogger *reporter;
    operation_mode mode;
    vector<char> *errorneous_chars;
    string error_msg;
public:
    ErrorRecoverer(ErrorLogger *reporter, operation_mode mode);

    void recover(fstream *input, streamoff start_pos, int line, int line_pos, operation_mode mode);

    const vector<char> *get_errorneous_chars() const {
        return errorneous_chars;
    }

    const string &get_error_msg() const {
        return error_msg;
    }

    void report();


};


#endif //PROJECT_ERRORRECOVERER_H
