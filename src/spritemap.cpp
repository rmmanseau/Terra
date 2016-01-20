#include "spritemap.h"

#define ROOT_DIR "../"

void SpriteMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &spriteSheet;

    target.draw(vertices, states);
}

SpriteMap::SpriteMap(int _tileSize, const std::string& fileName)
{
    if (!spriteSheet.loadFromFile(ROOT_DIR + fileName))
        throw std::invalid_argument(fileName + " could not be found.");

    tileSize = _tileSize;
    vertices.setPrimitiveType(sf::Quads);
}

void SpriteMap::addSprite(Vec2f pos, Vec2i tex, const sf::Color& color)
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

    quad[0].color = color * sf::Color(200, 200, 200);
    quad[1].color = color;
    quad[2].color = color * sf::Color(150, 150, 150);
    quad[3].color = color * sf::Color(50,50,50);

    sf::Vertex quad2[4];

    quad2[0].position = sf::Vector2f(200, 200);
    quad2[1].position = sf::Vector2f(300, 200);
    quad2[2].position = sf::Vector2f(300, 300);
    quad2[3].position = sf::Vector2f(200, 300);
    
    quad2[0].color = sf::Color::White * sf::Color(200, 200, 200);
    quad2[1].color = sf::Color::White;
    quad2[2].color = sf::Color::White * sf::Color(150, 150, 150);
    quad2[3].color = sf::Color::White * sf::Color(50, 50, 50);
    
    vertices.append(quad[0]);
    vertices.append(quad[1]);
    vertices.append(quad[2]);
    vertices.append(quad[3]);

    vertices.append(quad2[0]);
    vertices.append(quad2[1]);
    vertices.append(quad2[2]);
    vertices.append(quad2[3]);
}

void SpriteMap::clearSprites()
{
    vertices.clear();
}
