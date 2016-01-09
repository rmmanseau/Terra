#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

class Background : public sf::Drawable
{
    sf::Texture texture;
    sf::Sprite sprite;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    Background(int width, int height, const std::string& fileName, const sf::Color& color);
};

#endif // BACKGROUND_H
