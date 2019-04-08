//
// Created by mario_hunter on 4/8/19.
//

#ifndef PROJECT_LEXICALCOMPONENT_H
#define PROJECT_LEXICALCOMPONENT_H


#include <Component.h>
#include <fstream>

using namespace std;

class LexicalComponent : Component{
private:
    fstream *input;
    fstream *config;
    fstream* out_stream;

public:
    LexicalComponent(std::fstream *config, std::fstream *input);

    void *process_next_input() override;

    fstream *get_write_stream() override;

    void notify() override;

private:


    void
    build_component();
};


#endif //PROJECT_LEXICALCOMPONENT_H
