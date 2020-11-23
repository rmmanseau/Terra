#ifndef TERRARIUM_H
#define TERRARIUM_H

#include "common.h"
#include "entity.h"
#include "grid.h"
#include "factory.h"

#include "yaml-cpp/yaml.h"

class Terrarium
{
    sf::RenderWindow window;
    sf::Event event;

    Factory factory;
    Grid grid;

    EntityMap entities;
    ProcessVec processes;

public:
    Terrarium(YAML::Node config);
    void update(int timeStep);

    sf::RenderWindow& getWindow();
    sf::Event& getEvent();
    Grid& getGrid();
    Factory& getFactory();
    EntityMap& getEntities();
    ProcessVec& getProcesses();
};

#endif // TERRARIUM_H
