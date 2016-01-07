#ifndef PRENDER_H
#define PRENDER_H

#include "common.h"
#include "process.h"
#include "actor.h"
#include "spritemap.h"
#include "background.h"

class PRender : public Process
{
    sf::RenderWindow* pWindow;
    
    SpriteMap sprites;
    Background background;

public:
    bool init(sf::RenderWindow& window, int width, int height, int tileSize);
    virtual void update(ActorMap& actors);
};

#endif // PRENDER_H
