#include "prender.h"

#include "actor.h"
#include "cposition.h"
#include "crender.h"

bool PRender::init(sf::RenderWindow& window, int width, int height, int tileSize)
{
    if (!background.init(width*tileSize, height*tileSize,
                         "../assets/textures/dirt.png",
                         sf::Color(133, 87, 35)))
        return false;

    if (!sprites.init(tileSize, "../assets/textures/sprite_sheet_8.png"))
        return false;

    pWindow = &window;
    pWindow->draw(background);
    pWindow->display();

    return true;    
}

void PRender::update(ActorMap& actors)
{
    auto end = actors.end();
    for (auto itr = actors.begin(); itr != end; ++itr)
    {
        Actor& current = itr->second;
        std::shared_ptr<CPosition> pos = current.getComponent<CPosition>().lock();
        std::shared_ptr<CRender> render = current.getComponent<CRender>().lock();
        
        if (pos && render)
        {
            sprites.addSprite(pos->getPos(), render->getTexCoords(), render->getColor());
        }
    }

    pWindow->draw(background);
    pWindow->draw(sprites);
    pWindow->display();

    sprites.clearSprites();
}


