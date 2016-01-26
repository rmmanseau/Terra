#include "crender.h"

SRC_FACTORY_REGISTER(CRender);

bool CRender::init(YAML::Node node)
{
    try
    {
        YAML::const_iterator itr = node.begin();
        for (itr; itr != node.end(); ++itr)
        {
            Layer layer;
            layer.texCoords = Vec2i((*itr)["texpos"][0].as<int>(),
                                    (*itr)["texpos"][1].as<int>());
            layer.color = sf::Color((*itr)["color"][0].as<int>(),
                                    (*itr)["color"][1].as<int>(),
                                    (*itr)["color"][2].as<int>());
            layers.push_back(layer);
        }
    }
    catch (...)
    {
        return false;
    }
    return true;
}

// Vec2i CRender::getTexCoords()
// {
//     return texCoords;
// }
// sf::Color CRender::getColor()
// {
//     return color;
// }