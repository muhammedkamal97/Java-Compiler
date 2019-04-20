//
// Created by mario_hunter on 4/19/19.
//

#include <errors/ErrorLogger.h>
#include <parser/errors/ErrorRecoverer.h>
#include "PredictiveParser.h"

PredictiveParser::PredictiveParser(Production ***pdt, unordered_map<string, int> *non_terminal_map,
                                   unordered_map<string, int> *terminal_map, GrammarSymbol *start_symbol)
        : pdt(pdt), non_terminal_map(non_terminal_map), terminal_map(terminal_map) {
    productions_stack = new stack<GrammarSymbol *>();
    productions_stack->push(nullptr);
    this->start_symbol = start_symbol;
    productions_stack->push(this->start_symbol);
    parse_tree = new queue<Production *>();
    error_logger = new ErrorLogger();
    error_recoverer = new ErrorRecoverer(error_logger);
}

bool
PredictiveParser::has_next_production() {
    return productions_stack->size() > 0;
}

vector<Production *> *
PredictiveParser::next_production(Token *tkn) {

    GrammarSymbol *gram_symbol = productions_stack->top();
    auto res_prod = new vector<Production *>();
    if ((tkn == nullptr || tkn->type->name == "$") && productions_stack->size() == 1) {
        //both input and productions ended gracefully
        successfully_terminated = true;
        productions_stack->pop();
        return nullptr;

    } else if (gram_symbol->type == Terminal) {
        if ((gram_symbol->value) == tkn->type->name) {
            productions_stack->pop();
            return nullptr;
        }else{
            error(tkn, nullptr);
            return next_production(tkn);
        }

    } else if (gram_symbol->type == NonTerminal) {
        int non_terminal_index = non_terminal_map->at(gram_symbol->value);
        int terminal_index = terminal_map->at(tkn->type->name);

        Production *prod = pdt[non_terminal_index][terminal_index];
        if (prod == nullptr || prod->is_sync) {
            error(tkn, prod);
            return nullptr;
        }

        productions_stack->pop();

        push_to_stack(prod);

        parse_tree->push(prod);
        res_prod->push_back(prod);
        auto tmp = next_production(tkn);
        if (tmp != nullptr) res_prod->insert(res_prod->end(), tmp->begin(), tmp->end());
        return res_prod;
    }
    error(tkn, nullptr);
    return nullptr;
}

void
PredictiveParser::error(Token *tkn, Production *prod) {
    error_recoverer->recover(productions_stack, tkn, prod);

}

void
PredictiveParser::push_to_stack(Production *production) {
    auto symbols = production->productions->at(0);

    auto it = symbols->rbegin();

    while (it != symbols->rend()) {
        if (!((*it)->is_epsilon))productions_stack->push((*it));
        it++;
    }
}

bool
PredictiveParser::has_successfully_terminated() const {
    return successfully_terminated;
}
