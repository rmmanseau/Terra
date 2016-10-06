#include "glbl_constants.h"
#include "yaml-cpp/yaml.h"

const std::string CONFIG_DIR = "../";

void Constants::init()
{
    m_eTypeNull = 0;
    m_eTypeReserved = 1;
    m_eTypeEmpty = 2;

    YAML::Node globalConfig = YAML::LoadFile(CONFIG_DIR + "assets/global_conf.yaml");
    m_targetCycleTime = globalConfig["target_cycle_time"].as<int>();
}

Constants glbl::constants;
