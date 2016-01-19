#ifndef CRENDER_H
#define CRENDER_H

#include "common.h"
#include "component.h"
#include "vec2.h"

class CRender : public Component
{
    INC_FACTORY_REGISTER(CRender);

    Vec2 texCoords;
    sf::Color color;

public:
    virtual bool init(YAML::Node node);

    Vec2 getTexCoords();
    sf::Color getColor();
};

#endif // CRENDER_H
