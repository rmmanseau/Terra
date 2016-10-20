#include "background.h"
#include "glbl_assets.h"

Background::Background() {}

void Background::init(int width, int height, const std::string& fileName, const sf::Color& color)
{
    if (!glbl::assets.loadTexture(fileName, texture))
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

void Background::setSize(int w, int h)
{
    sprite.setTextureRect(sf::IntRect(0, 0, w, h));
}