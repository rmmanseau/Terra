#include "pmovement.h"

#include "entity.h"
#include "cposition.h"
#include "cmovement.h"

PMovement::PMovement(Grid& grid)
    : pGrid(grid)
{}

void PMovement::update(EntityMap& entities)
{
    for (auto itr = entities.begin();
        itr != entities.end(); ++itr)
    {
        Entity& current = itr->second;
        
        std::shared_ptr<CMovement> move = current.getComponent<CMovement>().lock();
        std::shared_ptr<CPosition> pos = current.getComponent<CPosition>().lock();

        if (move && pos)
        {
            Vec2 newPos = pos->getPos() + move->getDisplacement();
            if (pGrid.empty(newPos) && pGrid.inside(newPos))
            {
                pGrid.erase(pos->getPos());
                pGrid.setIdAt(newPos, current.getId());
                pos->setPos(newPos);
            }
        }
    }
}
