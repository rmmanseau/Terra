#include "terrarium.h"

void Terrarium::init(int width, int height)
{
    grid = Grid(width, height);

    picasso.init(width, height, 8);
    china.init(*this);

    for (int i = 0; i < width*height; ++i)
    {
        if ((i+1)%width == 0 || i%width == 0 || i/width == 0 || i/width == (height-1))
            china.assembleActor(actors, "Rock", Vec2(i%width, i/width));
    }

    china.assembleActor(actors, "DumbBug", Vec2(40, 40));
    china.assembleActor(actors, "DumbBug", Vec2(2, 2));
    china.assembleActor(actors, "DumbBug", Vec2(80, 20));
    china.assembleActor(actors, "DumbBug", Vec2(81, 20));
    china.assembleActor(actors, "DumbBug", Vec2(82, 20));
    china.assembleActor(actors, "DumbBug", Vec2(83, 20));
    china.assembleActor(actors, "DumbBug", Vec2(84, 20));
    china.assembleActor(actors, "DumbBug", Vec2(85, 20));
    china.assembleActor(actors, "DumbBug", Vec2(86, 20));
    china.assembleActor(actors, "DumbBug", Vec2(87, 20));
    china.assembleActor(actors, "DumbBug", Vec2(88, 20));
    china.assembleActor(actors, "DumbBug", Vec2(89, 20));
    china.assembleActor(actors, "DumbBug", Vec2(90, 20));
    china.assembleActor(actors, "DumbBug", Vec2(91, 20));
    china.assembleActor(actors, "Grass", Vec2(9, 10));
    china.assembleActor(actors, "Grass", Vec2(10, 10));
    china.assembleActor(actors, "Grass", Vec2(9, 11));
    china.assembleActor(actors, "Grass", Vec2(10, 11));
    china.assembleActor(actors, "Grass", Vec2(11, 11));
    china.assembleActor(actors, "Grass", Vec2(12, 11));
    china.assembleActor(actors, "Grass", Vec2(13, 11));
    china.assembleActor(actors, "Grass", Vec2(10, 12));

    processes.push_back(std::make_shared<PMovement>(grid));

    for (auto itr = actors.begin();
         itr != actors.end(); ++itr)
    {
        Actor& current = itr->second;
        std::shared_ptr<CPosition> pos = current.getComponent<CPosition>().lock();
        if (pos)
        {
            grid.setIdAt(pos->getPos(), current.getId());
        }
    }
}

void Terrarium::update()
{
    for (auto itr = processes.begin();
         itr != processes.end(); ++itr)
    {
        (*itr)->update(actors);
    }

    picasso.update(actors);
}

RenderSys* Terrarium::getRenderer()
{
    return &picasso;
}
