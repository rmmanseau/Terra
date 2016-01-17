#ifndef CTRANSLATE_H
#define CTRANSLATE_H

#include "common.h"
#include "component.h"
#include "vec2.h"

#include <cstdlib>
#include <map>

class CTranslate : public Component
{
    static const std::map<Dir, Vec2> dirMap;

    Dir direction;
    double velocity;

public:
    virtual bool init(YAML::Node node);

    void setDirection(Dir d);
    void setVelocity(double v);
    Vec2 getDisplacement();
};

inline std::shared_ptr<Component> createCTranslate()
{
    return std::make_shared<CTranslate>();
}

#endif // CTRANSLATE_H
