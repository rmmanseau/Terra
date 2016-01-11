#ifndef TERRARIUM_H
#define TERRARIUM_H

#include "common.h"
#include "entity.h"
#include "grid.h"
#include "factory.h"

class Terrarium
{
    sf::RenderWindow window;
    sf::Event event;

    Factory china;
    Grid grid;

    EntityMap entities;
    ProcessVec processes;

public:
    Terrarium(int width, int height, int tileSize);
    void update();

    sf::RenderWindow& getWindow();
    sf::Event& getEvent();
    Grid& getGrid();
    Factory& getFactory();
    EntityMap& getEntities();
    ProcessVec& getProcesses();
};

#endif // TERRARIUM_H
