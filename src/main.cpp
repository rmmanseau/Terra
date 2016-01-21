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

        // Random spikes in cycle time are probably due to cache misses
        // good luck future me.

        Terrarium t(40, 40, 12);
        
        sf::Clock gameClock;

        bool running = true;
        while (running)
        {
            gameClock.restart();
            
            t.update();

            int elapsed = gameClock.restart().asMicroseconds();
            int sleep = 10000 - elapsed;
            
            std::cout << "elapsed: " << elapsed << " sleep: " << sleep << std::endl;

            // sf::sleep(sf::microseconds(0));

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