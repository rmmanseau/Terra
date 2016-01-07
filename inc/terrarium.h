#ifndef TERRARIUM_H
#define TERRARIUM_H

#include "common.h"
#include "actor.h"
#include "grid.h"
#include "rendersys.h"
#include "factorysys.h"

#include "pmovement.h"

class Terrarium
{
    friend class FactorySys;
    
    ActorMap actors;
    ProcessVec processes;

    FactorySys china;
    Grid grid;
    RenderSys picasso;

public:
    void init(int width, int height);
    void update();

    RenderSys* getRenderer();
    std::shared_ptr<Grid> getGrid();
};

#endif // TERRARIUM_H
