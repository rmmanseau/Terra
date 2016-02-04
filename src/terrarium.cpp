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
    // china.assembleEntity(G_EntityNameTypeMap["DumbBugEgg"], Vec2i(2, 2));
    // china.assembleEntity(G_EntityNameTypeMap["DumbBugEgg"], Vec2i(3, 3));
    // china.assembleEntity(G_EntityNameTypeMap["DumbBugEgg"], Vec2i(4, 4));
    // china.assembleEntity(G_EntityNameTypeMap["DumbBugEgg"], Vec2i(80, 20));
    // china.assembleEntity(G_EntityNameTypeMap["DumbBugEgg"], Vec2i(81, 20));
    // china.assembleEntity(G_EntityNameTypeMap["DumbBugEgg"], Vec2i(82, 20));
    // china.assembleEntity(G_EntityNameTypeMap["DumbBugEgg"], Vec2i(83, 20));
    // china.assembleEntity(G_EntityNameTypeMap["DumbBugEgg"], Vec2i(84, 20));
    // china.assembleEntity(G_EntityNameTypeMap["DumbBugEgg"], Vec2i(85, 20));
    // china.assembleEntity(G_EntityNameTypeMap["DumbBugEgg"], Vec2i(86, 20));
    // china.assembleEntity(G_EntityNameTypeMap["DumbBugEgg"], Vec2i(87, 20));
    // china.assembleEntity(G_EntityNameTypeMap["DumbBugEgg"], Vec2i(88, 20));
    // china.assembleEntity(G_EntityNameTypeMap["DumbBugEgg"], Vec2i(89, 20));
    // china.assembleEntity(G_EntityNameTypeMap["DumbBugEgg"], Vec2i(90, 20));
    // china.assembleEntity(G_EntityNameTypeMap["DumbBugEgg"], Vec2i(91, 20));
    // china.assembleEntity(G_EntityNameTypeMap["Grass"], Vec2i(9, 10));
    // china.assembleEntity(G_EntityNameTypeMap["Grass"], Vec2i(10, 10));
    // china.assembleEntity(G_EntityNameTypeMap["Grass"], Vec2i(9, 11));
    // china.assembleEntity(G_EntityNameTypeMap["Grass"], Vec2i(10, 11));
    // china.assembleEntity(G_EntityNameTypeMap["Grass"], Vec2i(11, 11));
    // china.assembleEntity(G_EntityNameTypeMap["Grass"], Vec2i(12, 11));
    // china.assembleEntity(G_EntityNameTypeMap["Grass"], Vec2i(13, 11));
    // china.assembleEntity(G_EntityNameTypeMap["Grass"], Vec2i(10, 12));
    // china.assembleEntity(G_EntityNameTypeMap["Rock"], Vec2i(21, 30));
    // china.assembleEntity(G_EntityNameTypeMap["Rock"], Vec2i(21, 31));
    // china.assembleEntity(G_EntityNameTypeMap["Rock"], Vec2i(20, 30));
    // china.assembleEntity(G_EntityNameTypeMap["Rock"], Vec2i(20, 31));
    // china.assembleEntity(G_EntityNameTypeMap["Rock"], Vec2i(22, 31));
    // china.assembleEntity(G_EntityNameTypeMap["BlueRock"], Vec2i(50, 51));
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