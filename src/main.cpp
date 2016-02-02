#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "globals.h"
#include "helpers.h"
#include "terrarium.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <X11/Xlib.h>
#include "yaml-cpp/yaml.h"

#define ROOT_DIR "../"

void populateEntityNameTypeMap()
{
    YAML::Node entitySheet = YAML::LoadFile((std::string)ROOT_DIR + "assets/entities.yaml");

    int i = G_EntityNameTypeMap.size();
    for (YAML::const_iterator itr = entitySheet.begin();
         itr != entitySheet.end(); ++itr)
    {
        std::string name = itr->first.as<std::string>();
        EntityType type = (EntityType)(i++);

        G_EntityNameTypeMap.insert(std::make_pair(name, type));
    }
}

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

            int targetTime = 2000;
            int sleep = clamp(targetTime - elapsed, 0, targetTime);
            
            std::cout << "^^============elapsed: " << elapsed << " sleep: " << sleep << std::endl;

            sf::sleep(sf::microseconds(sleep));

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
    populateEntityNameTypeMap();
    
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