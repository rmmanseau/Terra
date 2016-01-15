#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "terrarium.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "yaml-cpp/yaml.h"

int main()
{
    try
    {
        
        srand(time(0));

        Terrarium t(50, 50, 12);
        
        sf::Clock gameClock;

        bool running = true;
        while (running)
        {
            t.update();

            int elapsed = gameClock.restart().asMilliseconds();
            int sleep = 2 - elapsed;
            
            std::cout << "elapsed: " << elapsed << " sleep: " << sleep << std::endl;

            sf::sleep(sf::milliseconds(0));
            gameClock.restart();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                running = false;
        }
    
    }
    catch (YAML::Exception &e)
    {
        std::cout << e.what() << std::endl;
        std::cout << "If error is at line 0 column 0, entities.yaml" 
                  << " probably wasn't found" << std::endl;
    }
    catch (...)
    {
        std::cout << "Building terrarium failed, exiting." << std::endl;
    }
}