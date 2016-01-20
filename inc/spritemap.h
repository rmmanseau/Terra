#ifndef SPRITEMAP_H
#define SPRITEMAP_H

#include <SFML/Graphics.hpp>
#include "vec2.h"

class SpriteMap : public sf::Drawable, public sf::Transformable
{
    sf::VertexArray vertices;
    sf::Texture spriteSheet;
    int tileSize;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    SpriteMap(int _tileSize, const std::string& fileName);
    void addSprite(Vec2f position, Vec2i texCoords, const sf::Color& color);
    void clearSprites();
};

#endif // SPRITEMAP_H
