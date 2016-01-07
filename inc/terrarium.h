#ifndef TERRARIUM_H
#define TERRARIUM_H

#include "common.h"
#include "actor.h"
#include "grid.h"
#include "factorysys.h"

#include "prender.h"
#include "pmovement.h"

class Terrarium
{
    sf::RenderWindow window;
    sf::Event event;

    FactorySys china;
    Grid grid;

    ActorMap actors;
    ProcessVec processes;

public:
    void init(int width, int height);
    void update();
};

#endif // TERRARIUM_H
