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

        Terrarium t(120, 50);
        
        int i = 0;

        bool running = true;
        while (running)
        {
            t.update();

            sf::sleep(sf::milliseconds(30));

            std::cout << i++ << std::endl;

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