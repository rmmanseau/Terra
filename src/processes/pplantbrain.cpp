#include "pplantbrain.h"

#include "helpers.h"

PPlantBrain::PPlantBrain()
{}

PPlantBrain::Node::Node(std::weak_ptr<CPlantBrain> plantBrain,
                        std::weak_ptr<CPosition> position,
                        std::weak_ptr<CAlive> alive,
                        std::weak_ptr<CSurroundings> surroundings,
                        std::weak_ptr<CSpawn> spawn)
    : invalid(false)
    , plantBrain(plantBrain)
    , position(position)
    , alive(alive)
    , surroundings(surroundings)
    , spawn(spawn)
{}

void PPlantBrain::removeInvalidNodes()
{
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [](Node& node) { return node.invalid; }),
                nodes.end());
}

void PPlantBrain::registerEntity(Entity& entity)
{
    std::weak_ptr<CPlantBrain> plantBrain = entity.getComponent<CPlantBrain>();
    std::weak_ptr<CPosition> position = entity.getComponent<CPosition>();
    std::weak_ptr<CAlive> alive = entity.getComponent<CAlive>();
    std::weak_ptr<CSurroundings> surroundings = entity.getComponent<CSurroundings>();
    std::weak_ptr<CSpawn> spawn = entity.getComponent<CSpawn>();

    if (plantBrain.lock() && position.lock() && alive.lock() && surroundings.lock() && spawn.lock())
        nodes.push_back(Node(plantBrain, position, alive, surroundings, spawn));
}

void PPlantBrain::update()
{
    for (auto itr = nodes.begin();
         itr != nodes.end(); ++itr)
    {        
        std::shared_ptr<CPlantBrain> plantBrain = itr->plantBrain.lock();
        std::shared_ptr<CPosition> position = itr->position.lock();
        std::shared_ptr<CAlive> alive = itr->alive.lock();
        std::shared_ptr<CSurroundings> surroundings = itr->surroundings.lock();
        std::shared_ptr<CSpawn> spawn = itr->spawn.lock();

        if (plantBrain && position && alive && surroundings && spawn)
        {
            int surroundingEntities = surroundings->numberFull();
            if (surroundingEntities != 7 && surroundingEntities != 6)
            {
                if (alive->getEnergy() >= spawn->energyRequired && surroundingEntities <= 4)
                {
                    spawn->active = true;
                    spawn->pos = randomAdjacentTile(position->getPos());
                    alive->updateEnergy(-spawn->energyCost);
                }

                if      (surroundingEntities <= 0)
                    alive->updateEnergy(3);
                else if (surroundingEntities <= 3)
                    alive->updateEnergy(2);
                else if (surroundingEntities <= 5)
                    alive->updateEnergy(1);
                else if (surroundingEntities <= 7)
                    alive->updateEnergy(0);
                else if (surroundingEntities <= 8)
                    alive->updateEnergy(-2);   
            }
        }
        else
        {
            itr->invalid = true;
        }
    }
    removeInvalidNodes();
}
