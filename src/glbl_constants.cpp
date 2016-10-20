#include "glbl_constants.h"
#include "yaml-cpp/yaml.h"

const std::string CONFIG_DIR = "../";

void Constants::init()
{
    m_entityTypeNull = 0;
    m_entityTypeReserved = 1;
    m_entityTypeEmpty = 2;
    m_entityNameToEntityTypeMap.insert(std::make_pair("Null", m_entityTypeNull));
    m_entityNameToEntityTypeMap.insert(std::make_pair("Reserved", m_entityTypeReserved));
    m_entityNameToEntityTypeMap.insert(std::make_pair("Empty", m_entityTypeEmpty));
    m_entityTypeToEntityNameMap.insert(std::make_pair(m_entityTypeNull, "Null"));
    m_entityTypeToEntityNameMap.insert(std::make_pair(m_entityTypeReserved, "Reserved"));
    m_entityTypeToEntityNameMap.insert(std::make_pair(m_entityTypeEmpty, "Empty"));

    YAML::Node globalConfig = YAML::LoadFile(CONFIG_DIR + "assets/global_conf.yaml");
    m_targetCycleTime = globalConfig["target_cycle_time"].as<int>();

    YAML::Node entitySheet = YAML::LoadFile(CONFIG_DIR + globalConfig["entities_conf_path"].as<std::string>());
    int i = m_entityNameToEntityTypeMap.size();
    for (YAML::const_iterator itr = entitySheet.begin();
         itr != entitySheet.end(); ++itr)
    {
        std::string name = itr->first.as<std::string>();
        EntityType type = (EntityType)(i++);

        m_entityNameToEntityTypeMap.insert(std::make_pair(name, type));
        m_entityTypeToEntityNameMap.insert(std::make_pair(type, name));
    }
}

int Constants::eAmount()
{
    return m_entityNameToEntityTypeMap.size();
}
EntityType Constants::eType(std::string name)
{
    return m_entityNameToEntityTypeMap[name];
}
std::string Constants::eName(EntityType type)
{
    return m_entityTypeToEntityNameMap[type];
}

Constants glbl::constants;
