#ifndef PRENDER_H
#define PRENDER_H

#include "common.h"
#include "process.h"
#include "spritemap.h"
#include "background.h"

#include "entity.h"
#include "cposition.h"
#include "crender.h"

class PRender : public Process
{
    struct Node
    {
        EntityId id;

        std::shared_ptr<CPosition> position;
        std::shared_ptr<CRender> render;
    };

    std::vector<Node> nodes;
    sf::RenderWindow& rWindow;
    
    SpriteMap sprites;
    Background background;

public:
    PRender(sf::RenderWindow& window, int width, int height, int tileSize);

    virtual void registerEntity(Entity& entity);
    virtual void unregisterEntity(EntityId id);
    virtual void update();
};

#endif // PRENDER_H
