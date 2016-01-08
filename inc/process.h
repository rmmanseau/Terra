#ifndef PROCESS_H
#define PROCESS_H

#include "common.h"

struct Process
{
    virtual void update(EntityMap& entities) = 0;
    virtual ~Process() {}
};

#endif // PROCESS_H