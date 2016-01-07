#include "factorysys.h"
#include "terrarium.h"

#include <string>

std::shared_ptr<Component> FactorySys::createCRender(YAML::Node node)
{
    std::shared_ptr<CRender> comp = std::make_shared<CRender>();
    RenderSys* pRenderer = pOwner->getRenderer();
    comp->setTexture(pRenderer->getTexture(node["img"].as<std::string>()));
    comp->setColor(sf::Color(node["color"][0].as<int>(),
                              node["color"][1].as<int>(),
                              node["color"][2].as<int>()));
    return std::static_pointer_cast<Component>(comp);
}

std::shared_ptr<Component> FactorySys::createCPosition(YAML::Node node)
{
    std::shared_ptr<CPosition> comp = std::make_shared<CPosition>();
    comp->setPos(Vec2(node["pos"][0].as<int>(),
                      node["pos"][1].as<int>()));
    return std::static_pointer_cast<Component>(comp);
}

std::shared_ptr<Component> FactorySys::createCMovement(YAML::Node node)
{
    std::shared_ptr<CMovement> comp = std::make_shared<CMovement>();
    return std::static_pointer_cast<Component>(comp);
}

void FactorySys::init(Terrarium& owner)
{
    pOwner = &owner;
    nextId = 1;

    YAML::Node actorSheet = YAML::LoadFile("../assets/actors.yaml");
    for (YAML::const_iterator itr = actorSheet.begin();
         itr != actorSheet.end(); ++itr)
    {
        blueprints.insert(std::make_pair(itr->first.as<std::string>(),
                                         itr->second));
    }

    componentCreators.insert(std::make_pair("CRender", &FactorySys::createCRender));
    componentCreators.insert(std::make_pair("CPosition", &FactorySys::createCPosition));
    componentCreators.insert(std::make_pair("CMovement", &FactorySys::createCMovement));
}

void FactorySys::assembleActor(ActorMap& actors, std::string actorName, Vec2 pos)
{
    auto blueprint = blueprints.find(actorName);
    YAML::Node components;

    if (blueprint != blueprints.end())
    {
        components = blueprint->second;
    }
    else
    {
        std::cout << "Failed to find blueprints for \"" << actorName << "\" actor" << std::endl
                  << "Terminating assembly process" << std::endl;
    }

    Actor actor(newId());

    for (YAML::const_iterator itr = components.begin();
         itr != components.end(); ++itr)
    {
        std::string componentName = itr->first.as<std::string>();
        YAML::Node componentNode = itr->second;

        auto result = componentCreators.find(componentName);
        if (result != componentCreators.end())
        {
            auto creator = result->second;
            std::shared_ptr<Component> component = (this->*creator)(componentNode);

            if (component != nullptr)
            {
                actor.addComponent(component);
            }
            else
            {
                std::cout << "Failed to assemble \"" << componentName << "\" component." << std::endl
                          << "Terminating incomplete actor." << std::endl;
                return;
            }
        }
        else
        {
            std::cout << "Failed to find \"" << componentName << "\" component." << std::endl
                      << "Terminating incomplete actor." << std::endl;
            return;
        }
    }

    std::shared_ptr<CPosition> position = actor.getComponent<CPosition>().lock();
    if (position)
    {
        position->setPos(pos);
    }

    actors.insert(std::make_pair(actor.getId(), actor));
}