#include "crender.h"

bool CRender::init(YAML::Node node)
{
    texCoords = Vec2(node["texpos"][0].as<int>(),
                     node["texpos"][1].as<int>());
    color = sf::Color(node["color"][0].as<int>(),
                      node["color"][1].as<int>(),
                      node["color"][2].as<int>());
    return true;
}

void CRender::setTexCoords(Vec2 tex)
{
    texCoords = tex;
}
void CRender::setColor(sf::Color _color)
{
    color = _color;
}
Vec2 CRender::getTexCoords()
{
    return texCoords;
}
sf::Color CRender::getColor()
{
    return color;
}