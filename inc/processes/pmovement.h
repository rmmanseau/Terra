#ifndef PMOVEMENT_H
#define PMOVEMENT_H

#include "common.h"
#include "process.h"
#include "grid.h"

class PMovement : public Process
{
    Grid& pGrid;

public:
    PMovement(Grid& grid);
    virtual void update(EntityMap& entities);
};

#endif // PMOVEMENT_H
