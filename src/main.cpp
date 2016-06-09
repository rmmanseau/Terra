#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "yaml-cpp/yaml.h"
#include <boost/filesystem.hpp>
#include <X11/Xlib.h>

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "globals.h"
#include "helpers.h"
#include "terrarium.h"
#include "terrariumeditor.h"

const std::string ROOT_DIR = "../";
// #define ROOT_DIR "../"

void loadGlobalSettings()
{
    YAML::Node globalConfig = YAML::LoadFile(ROOT_DIR + "assets/global_conf.yaml");

    G_Paths.insert(std::make_pair("textures", globalConfig["textures_path"].as<std::string>()));
    G_Paths.insert(std::make_pair("entities", globalConfig["entities_conf_path"].as<std::string>()));
    G_Paths.insert(std::make_pair("terrariums", globalConfig["terrariums_path"].as<std::string>()));
}

void populateEntityNameTypeMap()
{
    YAML::Node entitySheet = YAML::LoadFile(ROOT_DIR + G_Paths["entities"]);

    int i = G_EntityNameTypeMap.size();
    for (YAML::const_iterator itr = entitySheet.begin();
         itr != entitySheet.end(); ++itr)
    {
        std::string name = itr->first.as<std::string>();
        EntityType type = (EntityType)(i++);

        G_EntityNameTypeMap.insert(std::make_pair(name, type));
    }
}

void listTerrariums()
{
    using namespace boost::filesystem;
    path terrariumDir(ROOT_DIR + G_Paths["terrariums"]);

    try
    {
        if (exists(terrariumDir) && is_directory(terrariumDir))
        {            
            std::vector<path> terrariums;
            copy(directory_iterator(terrariumDir), directory_iterator(), back_inserter(terrariums));
            sort(terrariums.begin(), terrariums.end());

            for (auto itr = terrariums.begin(); itr != terrariums.end(); ++itr)
            {
                std::cout << itr->stem().string() << std::endl;
            }
        }
    }
    catch(const filesystem_error& fe)
    {
        std::cout << fe.what() << std::endl;
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

        std::string terrariumPath
            = ROOT_DIR + G_Paths["terrariums"] + terrariumName + ".yaml";

        YAML::Node terraConfig = YAML::LoadFile(terrariumPath);

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

            int targetTime = 30000;
            int sleep = clamp(targetTime - elapsed, 0, targetTime);
            
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

void runTerrariumBlueprintEditor(std::string blueprintPath)
{
    TerrariumEditor editor(blueprintPath, G_Paths["entities"]);

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
    populateEntityNameTypeMap();

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