#include "terrarium.h"

#include "prender.h"
#include "ptranslate.h"
#include "pmovement.h"

#include "cposition.h"

Terrarium::Terrarium(int width, int height, int tileSize)
    : grid(width, height)
    , china(*this)
{
    processes.push_back(std::make_shared<PRender>(window, width, height, tileSize));
    processes.push_back(std::make_shared<PTranslate>(grid));
    processes.push_back(std::make_shared<PMovement>());
    
    for (int i = 0; i < width*height; ++i)
    {
        if ((i+1)%width == 0 || /*i%width == 0 ||*/ i/width == 0 || i/width == (height-1))
            china.assembleEntity("Rock", Vec2(i%width, i/width));
    }

    china.assembleEntity("DumbBug", Vec2(40, 40));
    china.assembleEntity("DumbBug", Vec2(2, 2));
    china.assembleEntity("DumbBug", Vec2(80, 20));
    china.assembleEntity("DumbBug", Vec2(81, 20));
    china.assembleEntity("DumbBug", Vec2(82, 20));
    china.assembleEntity("DumbBug", Vec2(83, 20));
    china.assembleEntity("DumbBug", Vec2(84, 20));
    china.assembleEntity("DumbBug", Vec2(85, 20));
    china.assembleEntity("DumbBug", Vec2(86, 20));
    china.assembleEntity("DumbBug", Vec2(87, 20));
    china.assembleEntity("DumbBug", Vec2(88, 20));
    china.assembleEntity("DumbBug", Vec2(89, 20));
    china.assembleEntity("DumbBug", Vec2(90, 20));
    china.assembleEntity("DumbBug", Vec2(91, 20));
    china.assembleEntity("Grass", Vec2(9, 10));
    china.assembleEntity("Grass", Vec2(10, 10));
    china.assembleEntity("Grass", Vec2(9, 11));
    china.assembleEntity("Grass", Vec2(10, 11));
    china.assembleEntity("Grass", Vec2(11, 11));
    china.assembleEntity("Grass", Vec2(12, 11));
    china.assembleEntity("Grass", Vec2(13, 11));
    china.assembleEntity("Grass", Vec2(10, 12));

    window.create(sf::VideoMode(width*tileSize, height*tileSize, 32),
              "Terra",
              sf::Style::Close);
}

void Terrarium::update()
{
    // std::cout << entities.size() << std::endl;

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