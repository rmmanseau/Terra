#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#include "terrarium.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "yaml-cpp/yaml.h"

#include "cposition.h"

#include <X11/Xlib.h>

void terrariumEditor()
{
    sf::RenderWindow window(sf::VideoMode(200, 200, 32),
                            "Terra - Editor",
                            sf::Style::Close);
    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }
            }
        }

        window.clear();
        window.display();
    }
}

void runTerrarium()
{
    XInitThreads();

    try
    {
        srand(time(0));

        YAML::Node terraConfig = YAML::LoadFile("../assets/terrarium.yaml");

        Terrarium t(terraConfig);

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

            int sleep = 2000 - elapsed;
            
            std::cout << "^^============elapsed: " << elapsed << " sleep: " << sleep << std::endl;

            sf::sleep(sf::microseconds(0));

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                running = false;
        }
    
    }
    catch (YAML::Exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Building terrarium failed, exiting." << std::endl;
    }
}

int main(int argc, char* argv[])
{
    std::vector<std::string> args(argv, argv+argc);
    
    if (argc == 1)
    {
        runTerrarium();
    }
    else
    {
        if (args[1] == "--editor")
        {
            terrariumEditor();
        }
    }
}