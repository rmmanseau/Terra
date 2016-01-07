#include "background.h"

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

bool Background::init(int width, int height, const std::string& fileName, const sf::Color& color)
{
    if (!texture.loadFromFile(fileName))
        return false;

    texture.setRepeated(true);

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, width, height));
    sprite.setColor(color);

    return true;
}
