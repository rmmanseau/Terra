#ifndef CRENDER_H
#define CRENDER_H

#include "common.h"
#include "component.h"
#include "vec2.h"

class CRender : public Component
{
    Vec2 texCoords;
    sf::Color color;

public:
    inline void setTexCoords(Vec2 tex)
    {
        texCoords = tex;
    }
    inline void setColor(sf::Color _color)
    {
        color = _color;
    }
    inline Vec2 getTexCoords()
    {
        return texCoords;
    }
    inline sf::Color getColor()
    {
        return color;
    }
};

#endif // CRENDER_H