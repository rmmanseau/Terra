#include "terrarium.h"

#include "prender.h"
#include "pmovement.h"

#include "cposition.h"

Terrarium::Terrarium(int width, int height, int tileSize)
    : grid(width, height)
    , china(*this)
{
    for (int i = 0; i < width*height; ++i)
    {
        if ((i+1)%width == 0 || /*i%width == 0 ||*/ i/width == 0 || i/width == (height-1))
            china.assembleEntity(entities, "Rock", Vec2(i%width, i/width));
    }

    china.assembleEntity(entities, "DumbBug", Vec2(40, 40));
    china.assembleEntity(entities, "DumbBug", Vec2(2, 2));
    china.assembleEntity(entities, "DumbBug", Vec2(80, 20));
    china.assembleEntity(entities, "DumbBug", Vec2(81, 20));
    china.assembleEntity(entities, "DumbBug", Vec2(82, 20));
    china.assembleEntity(entities, "DumbBug", Vec2(83, 20));
    china.assembleEntity(entities, "DumbBug", Vec2(84, 20));
    china.assembleEntity(entities, "DumbBug", Vec2(85, 20));
    china.assembleEntity(entities, "DumbBug", Vec2(86, 20));
    china.assembleEntity(entities, "DumbBug", Vec2(87, 20));
    china.assembleEntity(entities, "DumbBug", Vec2(88, 20));
    china.assembleEntity(entities, "DumbBug", Vec2(89, 20));
    china.assembleEntity(entities, "DumbBug", Vec2(90, 20));
    china.assembleEntity(entities, "DumbBug", Vec2(91, 20));
    china.assembleEntity(entities, "Grass", Vec2(9, 10));
    china.assembleEntity(entities, "Grass", Vec2(10, 10));
    china.assembleEntity(entities, "Grass", Vec2(9, 11));
    china.assembleEntity(entities, "Grass", Vec2(10, 11));
    china.assembleEntity(entities, "Grass", Vec2(11, 11));
    china.assembleEntity(entities, "Grass", Vec2(12, 11));
    china.assembleEntity(entities, "Grass", Vec2(13, 11));
    china.assembleEntity(entities, "Grass", Vec2(10, 12));

    processes.push_back(std::make_shared<PRender>(window, width, height, tileSize));
    processes.push_back(std::make_shared<PMovement>(grid));

    window.create(sf::VideoMode(width*tileSize, height*tileSize, 32),
              "Terra",
              sf::Style::Close);
}

void Terrarium::update()
{
    for (auto itr = processes.begin();
         itr != processes.end(); ++itr)
    {
        (*itr)->update(entities);
    }
}

sf::RenderWindow* Terrarium::getWindowPtr()
{
    return &window;
}
sf::Event* Terrarium::getEventPtr()
{
    return &event;
}
Grid* Terrarium::getGridPtr()
{
    return &grid;
}
Factory* Terrarium::getFactoryPtr()
{
    return &china;
}