#include "crender.h"

bool CRender::init(YAML::Node node)
{
    try
    {
    texCoords = Vec2(node["texpos"][0].as<int>(),
                     node["texpos"][1].as<int>());
    color = sf::Color(node["color"][0].as<int>(),
                      node["color"][1].as<int>(),
                      node["color"][2].as<int>());
    }
    catch (...)
    {
        return false;
    }
    return true;
}

Vec2 CRender::getTexCoords()
{
    return texCoords;
}
sf::Color CRender::getColor()
{
    return color;
}