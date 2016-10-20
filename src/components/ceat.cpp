#include "ceat.h"
#include "globals.h"
#include "glbl_constants.h"

SRC_FACTORY_REGISTER(CEat);

bool CEat::init(YAML::Node node)
{
    try
    {
        YAML::Node foodNode = node["food"];
        for (YAML::const_iterator itr = foodNode.begin();
             itr != foodNode.end(); ++itr)
        {
            EntityType type = glbl::constants.eType(itr->first.as<std::string>());
            
            food.push_back(type);
            energyFromFood.insert(std::make_pair(type, itr->second.as<int>()));
        }

        active = false;
    }
    catch (YAML::Exception &e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
    catch (...)
    {
        return false;
    }
    return true;
}

