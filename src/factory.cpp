#include "factory.h"
#include "terrarium.h"

#include "crender.h"
#include "cposition.h"
#include "ctranslate.h"

#include <string>

Factory::Factory(Terrarium& owner)
    : pOwner(&owner)
    , pGrid(pOwner->getGridPtr())
    , nextId(1)
{
    YAML::Node entitySheet = YAML::LoadFile("../assets/entities.yaml");

    for (YAML::const_iterator itr = entitySheet.begin();
         itr != entitySheet.end(); ++itr)
    {
        blueprints.insert(std::make_pair(itr->first.as<std::string>(),
                                         itr->second));
    }

    componentCreatorFunctions.insert(std::make_pair("CRender", &createCRender));
    componentCreatorFunctions.insert(std::make_pair("CPosition", &createCPosition));
    componentCreatorFunctions.insert(std::make_pair("CTranslate", &createCTranslate));
}

void Factory::assembleEntity(EntityMap& entities, std::string entityName, Vec2 pos)
{
    auto blueprint = blueprints.find(entityName);
    YAML::Node components;

    if (blueprint != blueprints.end())
    {
        components = blueprint->second;
    }
    else
    {
        std::cout << "Failed to find blueprints for \"" << entityName << "\" Entity" << std::endl
                  << "Terminating assembly process" << std::endl;
    }

    Entity entity(newId());

    for (YAML::const_iterator itr = components.begin();
         itr != components.end(); ++itr)
    {
        std::string componentName = itr->first.as<std::string>();
        YAML::Node componentNode = itr->second;

        auto result = componentCreatorFunctions.find(componentName);
        if (result != componentCreatorFunctions.end())
        {
            auto creator = result->second;
            std::shared_ptr<Component> component = (*creator)();
            bool initSuccess = component->init(componentNode);

            if (component != nullptr && initSuccess)
            {
                entity.addComponent(component);
            }
            else
            {
                std::cout << "Failed to assemble \"" << componentName << "\" component." << std::endl
                          << "Terminating incomplete entity." << std::endl;
                return;
            }
        }
        else
        {
            std::cout << "Failed to find \"" << componentName << "\" component." << std::endl
                      << "Terminating incomplete entity." << std::endl;
            return;
        }
    }

    std::shared_ptr<CPosition> position = entity.getComponent<CPosition>().lock();
    if (position)
    {
        position->setPos(pos);
        pGrid->setIdAt(pos, entity.getId());
    }

    entities.insert(std::make_pair(entity.getId(), entity));
}