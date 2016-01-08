#ifndef PRENDER_H
#define PRENDER_H

#include "common.h"
#include "process.h"
#include "entity.h"
#include "spritemap.h"
#include "background.h"

class PRender : public Process
{
    sf::RenderWindow* pWindow;
    
    SpriteMap sprites;
    Background background;

public:
    PRender(sf::RenderWindow& window, int width, int height, int tileSize);
    virtual void update(EntityMap& entities);
};

#endif // PRENDER_H
