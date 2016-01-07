#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "terrarium.h"
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(0));

    Terrarium t;
    t.init(120, 50);

    bool running = true;
    while (running)
    {
        t.update();

        sf::sleep(sf::milliseconds(50));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            running = false;
    }
}