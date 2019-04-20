//
// Created by mario_hunter on 4/20/19.
//

#include "ErrorRecoverer.h"

ErrorRecoverer::ErrorRecoverer(ErrorLogger *logger) : logger(logger) {}

void
ErrorRecoverer::recover(stack<GrammarSymbol *> *production_stack, Token *tkn, Production *entry) {
    if (production_stack->top()->type == Terminal) {
        while (production_stack->top()->type == Terminal && production_stack->top()->value != tkn->type->name) {
            string msg = string("Missing a terminal [" + production_stack->top()->value + "], it has been inserted\n");
            logger->report("Parser Module", msg, nullptr);
            production_stack->pop();
        }
        return;
    }
    if (entry != nullptr && entry->is_sync) {
        production_stack->pop();
        return;
    }

    string msg = string("discarding input symbol [" + tkn->type->name + "]\n");
    logger->report("Parser Module", msg, nullptr);


}
