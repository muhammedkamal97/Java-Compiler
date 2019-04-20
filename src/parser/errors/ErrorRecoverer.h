//
// Created by mario_hunter on 4/20/19.
//

#ifndef PROJECT_ERRORRECOVERER_H
#define PROJECT_ERRORRECOVERER_H


#include <parser/Production.h>
#include <stack>
#include <tokens/Token.h>
#include <errors/ErrorLogger.h>

class ErrorRecoverer {
    ErrorLogger * logger;
public:
    ErrorRecoverer(ErrorLogger *logger);

    void recover(stack<GrammarSymbol*> *production_stack, Token *tkn,Production* entry);

};


#endif //PROJECT_ERRORRECOVERER_H
