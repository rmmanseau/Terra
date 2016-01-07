#include "spritemap.h"

void SpriteMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &spriteSheet;

    target.draw(vertices, states);
}

bool SpriteMap::init(int _tileSize, const std::string& fileName)
{
    if (!spriteSheet.loadFromFile(fileName))
        return false;

    tileSize = _tileSize;
    vertices.setPrimitiveType(sf::Quads);
    return true;
}

void SpriteMap::addSprite(Vec2 pos, Vec2 tex, const sf::Color& color)
{
    pos *= tileSize;
    tex *= tileSize;

    sf::Vertex quad[4];

    quad[0].position = sf::Vector2f(pos.x, pos.y);
    quad[1].position = sf::Vector2f(pos.x + tileSize, pos.y);
    quad[2].position = sf::Vector2f(pos.x + tileSize, pos.y + tileSize);
    quad[3].position = sf::Vector2f(pos.x, pos.y + tileSize);

    quad[0].texCoords = sf::Vector2f(tex.x, tex.y);
    quad[1].texCoords = sf::Vector2f(tex.x + tileSize, tex.y);
    quad[2].texCoords = sf::Vector2f(tex.x + tileSize, tex.y + tileSize);
    quad[3].texCoords = sf::Vector2f(tex.x, tex.y + tileSize);

    quad[0].color = color;
    quad[1].color = color;
    quad[2].color = color;
    quad[3].color = color;

    vertices.append(quad[0]);
    vertices.append(quad[1]);
    vertices.append(quad[2]);
    vertices.append(quad[3]);
}

void SpriteMap::clearSprites()
{
    vertices.clear();
}