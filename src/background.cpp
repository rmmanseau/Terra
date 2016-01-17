#include "background.h"

#define ROOT_DIR "../"

Background::Background(int width, int height, const std::string& fileName, const sf::Color& color)
{
    if (!texture.loadFromFile(ROOT_DIR + fileName))
        throw std::invalid_argument(fileName + " could not be found.");

    texture.setRepeated(true);

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, width, height));
    sprite.setColor(color);
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}
