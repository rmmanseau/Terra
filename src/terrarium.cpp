#include "terrarium.h"

#include "prender.h"
#include "ptranslate.h"
#include "psurroundings.h"
#include "peggbrain.h"
#include "pplantbrain.h"
#include "pdumbbrain.h"
#include "pmovement.h"
#include "pspawn.h"
#include "peat.h"
#include "palive.h"

Terrarium::Terrarium(YAML::Node config)
    : china(*this)
    , grid()
{
    // Pull values from config
    int width = config["width"].as<int>();
    int height = config["height"].as<int>();
    int tileSize = config["tile_size"].as<int>();

    std::string spriteSheetPath = config["sprite_sheet"].as<std::string>();
    std::string dirtTexturePath = config["dirt_texture"].as<std::string>();
    sf::Color dirtColor = sf::Color(config["dirt_color"][0].as<int>(),
                                    config["dirt_color"][1].as<int>(),
                                    config["dirt_color"][2].as<int>());

    // Init grid and window
    grid.init(width, height);
    window.create(sf::VideoMode(width*tileSize, height*tileSize, 32),
              "Terra",
              sf::Style::Close);

    // Init processes
    processes.push_back(std::make_shared<PRender>(window, tileSize, spriteSheetPath,
                                                  dirtTexturePath, dirtColor));
    processes.push_back(std::make_shared<PTranslate>(grid));
    processes.push_back(std::make_shared<PSurroundings>(grid));
    processes.push_back(std::make_shared<PEggBrain>());
    processes.push_back(std::make_shared<PPlantBrain>());
    processes.push_back(std::make_shared<PDumbBrain>());
    processes.push_back(std::make_shared<PMovement>());
    processes.push_back(std::make_shared<PSpawn>(grid, china, entities));
    processes.push_back(std::make_shared<PEat>(entities));
    processes.push_back(std::make_shared<PAlive>(china));
    

    // Assemble Initial entities
    for (int i = 0; i < width*height; ++i)
    {
        if ((i+1)%width == 0 || i%width == 0 || i/width == 0 || i/width == (height-1))
        {
            EntityType type = G_EntityNameTypeMap[(rand() % 2) ? "Rock" : "Rock2"];
            china.assembleEntity(type, Vec2i(i%width, i/width));
        }
    }

    YAML::const_iterator itr = config["initial_entities"].begin();
    YAML::const_iterator end = config["initial_entities"].end();
    for (itr; itr != end; ++itr)
    {
        EntityType type = G_EntityNameTypeMap[(*itr)["type"].as<std::string>()];
        Vec2i pos((*itr)["pos"][0].as<int>(), (*itr)["pos"][1].as<int>());
        china.assembleEntity(type, pos);
    }
}

void Terrarium::update(int timeStep)
{
    sf::Clock timer;

    for (auto itr = processes.begin();
         itr != processes.end(); ++itr)
    {
        (*itr)->update(timeStep);
    }
    china.update();
    
    std::cout << "Main Update: " << timer.restart().asMicroseconds() << std::endl;
}

sf::RenderWindow& Terrarium::getWindow()
{
    return window;
}
sf::Event& Terrarium::getEvent()
{
    return event;
}
Grid& Terrarium::getGrid()
{
    return grid;
}
Factory& Terrarium::getFactory()
{
    return china;
}
EntityMap& Terrarium::getEntities()
{
    return entities;
}
ProcessVec& Terrarium::getProcesses()
{
    return processes;
}