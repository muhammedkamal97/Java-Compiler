//
// Created by mario_hunter on 4/19/19.
//

#ifndef PROJECT_PARSERBUFFERSLAVE_H
#define PROJECT_PARSERBUFFERSLAVE_H

#include "ComponentSlave.h"
#include <fstream>

class ParserBufferSlave : public ComponentSlave {
private:
    std::fstream* write_buffer;
public:
    ParserBufferSlave(std::fstream *write_buffer);


    std::fstream *get_write_stream() override;

    void notify(void *notification) override;

};


#endif //PROJECT_PARSERBUFFERSLAVE_H
