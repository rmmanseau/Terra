#ifndef CRENDER_H
#define CRENDER_H

#include "common.h"
#include "component.h"
#include "vec2.h"

class CRender : public Component
{
    INC_FACTORY_REGISTER(CRender);

public:

    struct Layer
    {
        Vec2i texCoords;
        sf::Color color;
    };

    std::vector<Layer> layers;

    virtual bool init(YAML::Node node);

    // Vec2i getTexCoords();
    // sf::Color getColor();
};

#endif // CRENDER_H
