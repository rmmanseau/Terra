#include "pmovement.h"

#include "entity.h"
#include "cposition.h"
#include "ctranslate.h"

PMovement::PMovement(Grid& grid)
    : pGrid(grid)
{}

void PMovement::update(EntityMap& entities)
{
    for (auto itr = entities.begin();
        itr != entities.end(); ++itr)
    {
        Entity& current = itr->second;
        
        std::shared_ptr<CTranslate> move = current.getComponent<CTranslate>().lock();
        std::shared_ptr<CPosition> pos = current.getComponent<CPosition>().lock();

        if (move && pos)
        {
            Vec2 newPos = pos->getPos() + move->getDisplacement();

            if (pos->getPos().floor() == newPos.floor())
            {
                pos->setPos(newPos);
            }
            else if (pGrid.empty(newPos.floor()) && pGrid.inside(newPos.floor()))
            {
                pGrid.erase(pos->getPos().floor());
                pGrid.setIdAt(newPos.floor(), current.getId());
                pos->setPos(newPos);
            }
        }
    }
}
