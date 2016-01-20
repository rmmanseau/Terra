#ifndef CRENDER_H
#define CRENDER_H

#include "common.h"
#include "component.h"
#include "vec2.h"

class CRender : public Component
{
    INC_FACTORY_REGISTER(CRender);

    Vec2i texCoords;
    sf::Color color;

public:
    virtual bool init(YAML::Node node);

    Vec2i getTexCoords();
    sf::Color getColor();
};

#endif // CRENDER_H
