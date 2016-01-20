#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "terrarium.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "yaml-cpp/yaml.h"

#include "cposition.h"

int main()
{
    try
    {
        srand(time(0));

        Terrarium t(120, 50, 12);
        
        sf::Clock gameClock;

        bool running = true;
        while (running)
        {
            gameClock.restart();
            
            t.update();

            int elapsed = gameClock.restart().asMicroseconds();
            int sleep = 1000 - elapsed;
            
            std::cout << "elapsed: " << elapsed << " sleep: " << sleep << std::endl;

            sf::sleep(sf::microseconds(sleep));

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