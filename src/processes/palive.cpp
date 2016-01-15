#include "palive.h"

PAlive::PAlive(Factory& factory)
    : rFactory(factory)
{}

PAlive::Node::Node(EntityId id, std::weak_ptr<CAlive> alive)
    : invalid(false)
    , id(id)
    , alive(alive)
{}

void PAlive::removeInvalidNodes()
{
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [](Node& node) { return node.invalid; }),
                nodes.end());
}

void PAlive::registerEntity(Entity& entity)
{
    std::weak_ptr<CAlive> alive = entity.getComponent<CAlive>();

    if (alive.lock())
        nodes.push_back(Node(entity.getId(), alive));
}

void PAlive::update()
{
    for (auto itr = nodes.begin();
         itr != nodes.end(); ++itr)
    {        
        std::shared_ptr<CAlive> alive = itr->alive.lock();

        if (alive)
        {
            if (alive->getHealth() == 0)
            {
                rFactory.disassembleEntity(itr->id);
            }

            if (alive->getEnergy() == 0)
                alive->updateHealth(-1);
        }
        else
        {
            itr->invalid = true;
        }
    }
    removeInvalidNodes();
}
