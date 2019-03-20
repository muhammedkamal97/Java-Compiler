//
// Created by mario_hunter on 3/19/19.
//

#ifndef PROJECT_COMPONENT_H
#define PROJECT_COMPONENT_H


#include <ostream>
#include "ComponentSlave.h"

class Component : ComponentSlave {
    /* attach a new slave buffer to this component to write ouput to*/
    virtual void attach_to_slave_port(ComponentSlave *slave) = 0;

    /* accept a new master to control the processing of input. Only one master can be accepted.
     * If the slave deems the master as acceptable -first to call, it will complete the handshake by calling the
     * handshake method on the master and passing itself to be controlled by the master.*/
    virtual void attach_to_master_channel(Component *master) = 0;

    /*handshake the slave after being accepted as master*/
    virtual void handshake_slave_channel(Component *slave) = 0;

    virtual void *process_next_input() = 0;

public:
    Component(std::fstream *config, std::fstream *input);

};


#endif //PROJECT_COMPONENT_H
