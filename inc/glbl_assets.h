#ifndef GLBL_ASSETS_H
#define GLBL_ASSETS_H

#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "yaml-cpp/yaml.h"
#include <boost/filesystem.hpp>


class Assets
{
    std::string configDirPath;
    std::string configPath;
    std::string entitiesPath;
    std::string terrariumsDirPath;
    std::string texturesDirPath;

public:

    Assets() {}
    void init(std::string confDirPath);

    bool writeTerrariumBlueprint(const std::string &terrariumName, const YAML::Emitter& out);
    YAML::Node loadConfig();
    YAML::Node loadEntities();
    YAML::Node loadTerrariumBlueprint(const std::string &terrariumName);
    bool loadTexture(const std::string &textureName, sf::Texture& texture);
    std::vector<std::string> getTerrariumNames();
};

namespace glbl
{
    extern Assets assets;
}

#endif // GLBL_ASSETS_H
