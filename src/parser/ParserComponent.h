//
// Created by mario_hunter on 4/19/19.
//

#ifndef PROJECT_PARSERCOMPONENT_H
#define PROJECT_PARSERCOMPONENT_H


#include <Component.h>
#include <fstream>
#include <tokens/TokenType.h>
#include <parser/analyzer/PredictiveParser.h>

class ParserComponent : public Component {
private:
    fstream *config;
    fstream *out_stream;
    PredictiveParser *pdt_parser;

    void
    build_component();

public:
    ParserComponent(fstream *config, fstream *input);

    void *process_next_input() override;

    fstream *get_write_stream() override;

    void notify(void* notification) override;


};


#endif //PROJECT_PARSERCOMPONENT_H
