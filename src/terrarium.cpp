#include "terrarium.h"

#include "prender.h"
#include "ptranslate.h"
#include "psurroundings.h"
#include "pplantbrain.h"
#include "pdumbbrain.h"
#include "pmovement.h"
#include "pspawn.h"
#include "peat.h"
#include "palive.h"

Terrarium::Terrarium(int width, int height, int tileSize)
    : china(*this)
    , grid(width, height)
{
    processes.push_back(std::make_shared<PRender>(window, width, height, tileSize));
    processes.push_back(std::make_shared<PTranslate>(grid));
    processes.push_back(std::make_shared<PSurroundings>(grid));
    processes.push_back(std::make_shared<PPlantBrain>());
    processes.push_back(std::make_shared<PDumbBrain>());
    processes.push_back(std::make_shared<PMovement>());
    processes.push_back(std::make_shared<PSpawn>(grid, china));
    processes.push_back(std::make_shared<PEat>(entities));
    processes.push_back(std::make_shared<PAlive>(china));
    
    for (int i = 0; i < width*height; ++i)
    {
        if ((i+1)%width == 0 || /*i%width == 0 ||*/ i/width == 0 || i/width == (height-1))
            china.assembleEntity(EntityType::Rock, Vec2i(i%width, i/width));
    }

    china.assembleEntity(EntityType::DumbBug, Vec2i(2, 2));
    china.assembleEntity(EntityType::DumbBug, Vec2i(3, 3));
    china.assembleEntity(EntityType::DumbBug, Vec2i(4, 4));
    china.assembleEntity(EntityType::DumbBug, Vec2i(80, 20));
    china.assembleEntity(EntityType::DumbBug, Vec2i(81, 20));
    china.assembleEntity(EntityType::DumbBug, Vec2i(82, 20));
    china.assembleEntity(EntityType::DumbBug, Vec2i(83, 20));
    china.assembleEntity(EntityType::DumbBug, Vec2i(84, 20));
    china.assembleEntity(EntityType::DumbBug, Vec2i(85, 20));
    china.assembleEntity(EntityType::DumbBug, Vec2i(86, 20));
    china.assembleEntity(EntityType::DumbBug, Vec2i(87, 20));
    china.assembleEntity(EntityType::DumbBug, Vec2i(88, 20));
    china.assembleEntity(EntityType::DumbBug, Vec2i(89, 20));
    china.assembleEntity(EntityType::DumbBug, Vec2i(90, 20));
    china.assembleEntity(EntityType::DumbBug, Vec2i(91, 20));
    china.assembleEntity(EntityType::Grass, Vec2i(9, 10));
    china.assembleEntity(EntityType::Grass, Vec2i(10, 10));
    china.assembleEntity(EntityType::Grass, Vec2i(9, 11));
    china.assembleEntity(EntityType::Grass, Vec2i(10, 11));
    china.assembleEntity(EntityType::Grass, Vec2i(11, 11));
    china.assembleEntity(EntityType::Grass, Vec2i(12, 11));
    china.assembleEntity(EntityType::Grass, Vec2i(13, 11));
    china.assembleEntity(EntityType::Grass, Vec2i(10, 12));
    china.assembleEntity(EntityType::Rock, Vec2i(21, 30));
    china.assembleEntity(EntityType::Rock, Vec2i(21, 31));
    china.assembleEntity(EntityType::Rock, Vec2i(20, 30));
    china.assembleEntity(EntityType::Rock, Vec2i(20, 31));
    china.assembleEntity(EntityType::Rock, Vec2i(22, 31));

    window.create(sf::VideoMode(width*tileSize, height*tileSize, 32),
              "Terra",
              sf::Style::Close);
}

void Terrarium::update()
{
    // std::cout << entities.size() << std::endl;
    china.update();

    for (auto itr = processes.begin();
         itr != processes.end(); ++itr)
    {
        (*itr)->update();
    }
}

sf::RenderWindow& Terrarium::getWindow()
{
    return window;
}
sf::Event& Terrarium::getEvent()
{
    return event;
}
Grid& Terrarium::getGrid()
{
    return grid;
}
Factory& Terrarium::getFactory()
{
    return china;
}
EntityMap& Terrarium::getEntities()
{
    return entities;
}
ProcessVec& Terrarium::getProcesses()
{
    return processes;
}