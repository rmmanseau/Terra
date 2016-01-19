#include "factory.h"
#include "terrarium.h"
#include "process.h"
#include "cposition.h"

#include <string>

#define ROOT_DIR "../"

Factory::Factory(Terrarium& owner)
    : rGrid(owner.getGrid())
    , rProcesses(owner.getProcesses())
    , rEntities(owner.getEntities())
    , nextId(1)
{
    entityTypes.insert(std::make_pair("Rock", EntityType::Rock));
    entityTypes.insert(std::make_pair("Grass", EntityType::Grass));
    entityTypes.insert(std::make_pair("DumbBug", EntityType::DumbBug));
    
    YAML::Node entitySheet = YAML::LoadFile((std::string)ROOT_DIR + "assets/entities.yaml");
    for (YAML::const_iterator itr = entitySheet.begin();
         itr != entitySheet.end(); ++itr)
    {
        EntityType type = entityTypes[itr->first.as<std::string>()];
        YAML::Node node = itr->second;
        blueprints.insert(std::make_pair(type, node));
    }
}

std::shared_ptr<Component> Factory::assembleComponent(const std::string& name, const YAML::Node& initNode)
{
    FunctionMap::iterator result = componentCreators->find(name);
    if (result == componentCreators->end())
    {
        std::cout << "Failed to find \"" << name << "\""
                  << std::endl
                  << "Terminating incomplete entity." << std::endl;

        return std::shared_ptr<Component>();
    }

    std::shared_ptr<Component> comp = (result->second)();
    bool initSuccess = comp->init(initNode);

    if (!initSuccess)
    {
        std::cout << "Failed to assemble \"" << name << "\"" 
                  << std::endl
                  << "Terminating incomplete entity." << std::endl;

        return std::shared_ptr<Component>();
    }

    return comp;
}

void Factory::assembleEntity(EntityType type, Vec2 pos)
{
    if (!rGrid.inside(pos))
    {
        std::cout << "Attempted to assemble entity outside grid boundries." << std::endl
                  << "Terminating assembly process" << std::endl;
    }

    auto blueprint = blueprints.find(type);
    YAML::Node components;

    if (blueprint != blueprints.end())
    {
        components = blueprint->second;
    }
    else
    {
        std::cout << "Failed to find blueprints for entity type " << (int)type << std::endl
                  << "Terminating assembly process" << std::endl;
        return;
    }

    EntityId id = newId();
    Entity entity(id, type);

    for (YAML::const_iterator itr = components.begin();
         itr != components.end(); ++itr)
    {
        std::string name = itr->first.as<std::string>();
        YAML::Node initNode = itr->second;

        std::shared_ptr<Component> component = assembleComponent(name, initNode);

        if (component)
        {
            entity.addComponent(component);
        }
    }

    std::shared_ptr<CPosition> position = entity.getComponent<CPosition>();
    if (position)
    {
        position->setPos(pos);
        rGrid.setInfoAt(pos, id, type);
    }
    
    rEntities.insert(std::make_pair(id, entity));
    newEntities.push_back(id);
}

void Factory::disassembleEntity(EntityId id)
{
    Entity& entity = rEntities.at(id);
    std::shared_ptr<CPosition> position = entity.getComponent<CPosition>();

    deadEntities.push_back(id);
    rGrid.erase(position->getPos());
}

void Factory::update()
{
    for (auto deadId = deadEntities.begin(); deadId != deadEntities.end(); ++deadId)
    {
        for (auto p = rProcesses.begin(); p != rProcesses.end(); ++p)
        {
            (*p)->unregisterEntity(*deadId);
        }

        rEntities.erase(*deadId);
    }
    deadEntities.clear();

    for (auto e = newEntities.begin(); e != newEntities.end(); ++e)
    {
        for (auto p = rProcesses.begin(); p != rProcesses.end(); ++p)
        {
            (*p)->registerEntity(rEntities.at(*e));
        }
    }
    newEntities.clear();
}

int Factory::newId()
{
    return nextId++;
}

Factory::FunctionMap* Factory::getComponentCreators()
{
    if (!componentCreators)
        componentCreators = new FunctionMap;
    
    return componentCreators;
}

Factory::FunctionMap* Factory::componentCreators = nullptr;
