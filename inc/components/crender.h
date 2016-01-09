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
    bool init(YAML::Node node);

    Vec2 getTexCoords();
    sf::Color getColor();
};

inline std::shared_ptr<Component> createCRender()
{
    return std::make_shared<CRender>();
}

#endif // CRENDER_H