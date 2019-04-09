//
// Created by mario_hunter on 4/9/19.
//

#ifndef PROJECT_BUFFERSLAVE_H
#define PROJECT_BUFFERSLAVE_H


#include "ComponentSlave.h"
#include <fstream>

using namespace std;
class LexicalBufferSlave : public ComponentSlave{
private:
    fstream* write_buffer;
public:
    LexicalBufferSlave(fstream *write_buffer);

    std::fstream *get_write_stream() override;

    void notify(void *notification) override;
};


#endif //PROJECT_BUFFERSLAVE_H
