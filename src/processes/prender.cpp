#include "prender.h"

#include "entity.h"
#include "cposition.h"
#include "crender.h"

PRender::PRender(sf::RenderWindow& window, int width, int height, int tileSize)
    : background(width*tileSize, height*tileSize,
                 "../assets/textures/dirt.png", sf::Color(133, 87, 35))
    , sprites(tileSize, "../assets/textures/sprite_sheet_8.png")
{
    pWindow = &window;
}

void PRender::update(EntityMap& entities)
{
    auto end = entities.end();
    for (auto itr = entities.begin(); itr != end; ++itr)
    {
        Entity& current = itr->second;
        std::shared_ptr<CPosition> pos = current.getComponent<CPosition>().lock();
        std::shared_ptr<CRender> render = current.getComponent<CRender>().lock();
        
        if (pos && render)
        {
            sprites.addSprite(pos->getPos().floor(), render->getTexCoords(), render->getColor());
        }
    }

    pWindow->draw(background);
    pWindow->draw(sprites);
    pWindow->display();

    sprites.clearSprites();
}


