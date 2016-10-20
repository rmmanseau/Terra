#include "glbl_assets.h"

void Assets::init(std::string path)
{
    configDirPath = path;
    configPath = configDirPath + "config.yaml";


    YAML::Node globalConfig = YAML::LoadFile(configPath);

    entitiesPath = configDirPath + globalConfig["entities_conf_path"].as<std::string>();
    texturesDirPath = configDirPath + globalConfig["textures_path"].as<std::string>();
    terrariumsDirPath = configDirPath + globalConfig["terrariums_path"].as<std::string>();
}

bool Assets::writeTerrariumBlueprint(const std::string &terrariumName, const YAML::Emitter &out)
{
    try
    {
        std::ofstream savefile;
        std::string path = terrariumsDirPath + terrariumName + ".yaml";
        savefile.open(path);
        std::cout << path << std::endl;

        savefile << out.c_str() << std::endl;
        savefile.close();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

YAML::Node Assets::loadConfig()
{
    return YAML::LoadFile(configPath);
}

YAML::Node Assets::loadEntities()
{
    return YAML::LoadFile(entitiesPath);
}

YAML::Node Assets::loadTerrariumBlueprint(const std::string &terrariumName)
{
    return YAML::LoadFile(terrariumsDirPath + terrariumName + ".yaml");
}

bool Assets::loadTexture(const std::string &textureName, sf::Texture &texture)
{
    return texture.loadFromFile(texturesDirPath + textureName);
}

std::vector<std::string> Assets::getTerrariumNames()
{
    using namespace boost::filesystem;
    path terrariumDir(terrariumsDirPath);

    std::vector<std::string> names;

    try
    {
        if (exists(terrariumDir) && is_directory(terrariumDir))
        {            
            std::vector<path> terrariums;
            copy(directory_iterator(terrariumDir), directory_iterator(), back_inserter(terrariums));
            sort(terrariums.begin(), terrariums.end());

            for (auto itr = terrariums.begin(); itr != terrariums.end(); ++itr)
            {
                names.push_back(itr->stem().string());
            }
        }
    }
    catch(const filesystem_error& fe)
    {
        std::cout << fe.what() << std::endl;
    }

    return names;
}

Assets glbl::assets;
