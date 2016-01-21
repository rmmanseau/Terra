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

        Terrarium t(120, 60, 12);
        
        sf::Clock gameClock;
        sf::Clock sleepClock;

        int timeStep = 0;
        int elapsed = 0;

        bool running = true;
        while (running)
        {
            timeStep = gameClock.restart().asMicroseconds();
            sleepClock.restart();
            t.update(timeStep);
            elapsed = sleepClock.restart().asMicroseconds();

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