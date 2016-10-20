#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "yaml-cpp/yaml.h"
#include <X11/Xlib.h>

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "glbl_assets.h"
#include "glbl_helpers.h"
#include "terrarium.h"
#include "terrariumeditor.h"

void loadGlobalSettings()
{
    glbl::assets.init("/home/ryan/cs/projects/terra/conf/");
    glbl::constants.init();
    glbl::helpers.init();
}

void listTerrariums()
{
    std::vector<std::string> terrariums = glbl::assets.getTerrariumNames();
    for (int i = 0; i < terrariums.size(); ++i)
    {
        std::cout << terrariums.at(i) << std::endl;
    }
}

void printTerraDetails()
{
    std::cout << "\nTerra lets you create and watch the interactions between creatures in a virtual terrarium.\n\n"
              << "Usage:\n\n"
              << "./terra <terrarium>\n"
              << "./terra --editor <terrarium>\n\n"
              << "Existing terrariums:\n\n";

    listTerrariums();

    std::cout << std::endl;
}

void runTerrarium(std::string terrariumName)
{
    XInitThreads();

    try
    {
        srand(time(0));

        YAML::Node terraConfig = glbl::assets.loadTerrariumBlueprint(terrariumName);
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

            int targetTime = glbl::constants.targetCycleTime();
            int sleep = glbl::helpers.clamp(targetTime - elapsed, 0, targetTime);
            
            std::cout << "-\n"
                      << "Elapsed:\t" << elapsed << "\n"
                      << "Sleep:\t\t" << sleep   << "\n\n";

            sf::sleep(sf::microseconds(sleep));

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                running = false;
        }
    }
    catch (YAML::Exception &e)
    {
        std::cout << "\nInvalid map. Choose from the existing maps:\n" << std::endl;
        listTerrariums();
        std::cout << "\nYaml error message:\n" << e.what() << "\n" << std::endl;
    }
    catch (...)
    {
        std::cout << "Building terrarium failed, exiting." << std::endl;
    }
}

void runTerrariumBlueprintEditor(std::string blueprintName)
{
    TerrariumEditor editor(blueprintName);

    int winW = editor.blueprint.width * editor.blueprint.tileSize;
    int winH = editor.blueprint.height * editor.blueprint.tileSize;
    sf::RenderWindow window(sf::VideoMode(winW, winH, 32),
                            "Terra - Editor",
                            sf::Style::Close);
    window.setMouseCursorVisible(false);

    sf::Vector2i pos = sf::Mouse::getPosition(window);
    editor.cursor.position = Vec2i(pos.x / editor.blueprint.tileSize,
                                   pos.y / editor.blueprint.tileSize);

    sf::Event event;
    
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            editor.update(window, event);
        }
        
        sf::sleep(sf::microseconds(100));
    }
}

int main(int argc, char* argv[])
{
    std::vector<std::string> args(argv, argv+argc);

    loadGlobalSettings();

    if (argc == 1)
    {
        printTerraDetails();
    }
    else
    {
        if (args[1] == "--editor")
        {
            if (argc > 2)
                runTerrariumBlueprintEditor(args[2]);
            else
                runTerrariumBlueprintEditor("default");
        }
        else
        {
            runTerrarium(args[1]);
        }
    }
}
