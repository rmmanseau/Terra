#ifndef RENDERSYS_H
#define RENDERSYS_H

#include "common.h"
#include "crender.h"
#include "cposition.h"
#include "actor.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class RenderSys
{
    int tileSize;

    sf::RenderWindow window;
    sf::Sprite dirtSprite;
    TextureMap textures;

    void loadTextures(std::string path);

public:
    RenderSys() {};
    void init(int w, int h, int size);
    void update(ActorMap& actors);
    
    sf::Texture& getTexture(std::string texName);
};

#endif // RENDERSYS_H
