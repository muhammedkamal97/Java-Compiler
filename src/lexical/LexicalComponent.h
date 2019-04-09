//
// Created by mario_hunter on 4/8/19.
//

#ifndef PROJECT_LEXICALCOMPONENT_H
#define PROJECT_LEXICALCOMPONENT_H


#include <Component.h>
#include <fstream>
#include <lexical/analyzer/Tokenizer.h>
#include <tables/SimpleSymbolTable.h>

using namespace std;

class LexicalComponent : public Component{
private:
    fstream *input;
    fstream *config;
    fstream* out_stream;

public:
    LexicalComponent(std::fstream *config, std::fstream *input,SimpleSymbolTable *table);

    void *process_next_input() override;

    fstream *get_write_stream() override;

    void notify(void* notification) override;

private:


    void
    build_component();

    Tokenizer *dfa;
    SimpleSymbolTable *table;
};


#endif //PROJECT_LEXICALCOMPONENT_H
