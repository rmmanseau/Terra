#ifndef PROCESS_H
#define PROCESS_H

#include "common.h"

struct Process
{
    virtual void update(ActorMap& actors) = 0;
};

#endif // PROCESS_H