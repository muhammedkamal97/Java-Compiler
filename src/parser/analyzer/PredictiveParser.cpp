//
// Created by mario_hunter on 4/19/19.
//

#include "PredictiveParser.h"

PredictiveParser::PredictiveParser(Production ***pdt, unordered_map<string, int> *non_terminal_map,
                                   unordered_map<string, int> *terminal_map, GrammarSymbol *start_symbol)
        : pdt(pdt), non_terminal_map(non_terminal_map), terminal_map(terminal_map) {
    productions_stack = new stack<GrammarSymbol *>();
    productions_stack->push(nullptr);
    this->start_symbol = start_symbol;
    productions_stack->push(this->start_symbol);
    parse_tree = new queue<Production *>();
}

bool
PredictiveParser::has_next_production() {
    return productions_stack->size() > 0;
}

Production *
PredictiveParser::next_production(Token *tkn) {
    //TODO

    GrammarSymbol *gram_symbol = productions_stack->top();

    if (tkn == nullptr && productions_stack->size() == 1) {
        //both input and productions ended gracefully
        successfully_terminated = true;
        productions_stack->pop();
        return nullptr;

    } else if (gram_symbol->type == Terminal) {
        if ((gram_symbol->value) == tkn->type->name) {
            productions_stack->pop();
        } else {
            error();
        }

    } else if (gram_symbol->type == NonTerminal) {
        int non_terminal_index = non_terminal_map->at(gram_symbol->value);
        int terminal_index = terminal_map->at(tkn->type->name);

        Production *prod = pdt[non_terminal_index][terminal_index];
        if (prod == nullptr) error();

        productions_stack->pop();

        push_to_stack(prod);

        parse_tree->push(prod);
        next_production(tkn);
        return prod;
    }
    return nullptr;
}

void
PredictiveParser::error() {
    //TODO
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
