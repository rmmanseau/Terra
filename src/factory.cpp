#include "factory.h"
#include "terrarium.h"
#include "process.h"

#include "crender.h"
#include "cposition.h"
#include "ctranslate.h"
#include "calive.h"
#include "cmovement.h"

#include <string>

Factory::Factory(Terrarium& owner)
    : rGrid(owner.getGrid())
    , rEntities(owner.getEntities())
    , rProcesses(owner.getProcesses())
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
    componentCreatorFunctions.insert(std::make_pair("CAlive", &createCAlive));
    componentCreatorFunctions.insert(std::make_pair("CMovement", &createCMovement));
}

void Factory::assembleEntity(std::string entityName, Vec2 pos)
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

    EntityId id = newId();
    Entity entity(id);

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
                std::cout << "Failed to assemble \"" << componentName
                          << "\" component for " << entityName
                          << std::endl
                          << "Terminating incomplete entity." << std::endl;
                return;
            }
        }
        else
        {
            std::cout << "Failed to find \"" << componentName
                      << "\" component for " << entityName
                      << std::endl
                      << "Terminating incomplete entity." << std::endl;
            return;
        }
    }

    std::shared_ptr<CPosition> position = entity.getComponent<CPosition>().lock();
    if (position)
    {
        position->setPos(pos);
        rGrid.setIdAt(pos, id);
    }
    
    rEntities.insert(std::make_pair(id, entity));

    for (auto itr = rProcesses.begin(); itr != rProcesses.end(); ++itr)
    {
        (*itr)->registerEntity(entity);
    }
}