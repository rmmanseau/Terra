#ifndef CRENDER_H
#define CRENDER_H

#include "common.h"
#include "component.h"
#include "vec2.h"

class CRender : public Component
{
    sf::Sprite sprite;

public:
    inline sf::Sprite getSprite()
    {
        return sprite;
    }
    inline void setTexture(sf::Texture& texture)
    {
        sprite.setTexture(texture);
    }
    inline void setColor(sf::Color color)
    {
        sprite.setColor(color);
    }
    inline void setSpritePos(Vec2 pos)
    {
        sprite.setPosition(sf::Vector2f(pos.x, pos.y));
    }
};

#endif // CRENDER_H