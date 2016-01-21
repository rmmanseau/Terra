#include "prender.h"

PRender::PRender(sf::RenderWindow& window, int width, int height, int tileSize)
    : rWindow(window)
    , sprites(tileSize, "assets/textures/sprite_sheet_12.png")
    , background(width*tileSize, height*tileSize,
                 "assets/textures/dirt.png", sf::Color(133, 87, 35))
    , timeSinceLastDraw(0)
    , timeBetweenDraws((1./60) * 1000000)
{}

void PRender::registerEntity(Entity& entity)
{
    Node node;
    node.id = entity.getId();

    if (
        (node.position = entity.getComponent<CPosition>()) &&
        (node.render = entity.getComponent<CRender>())
       )
    {
        nodes.push_back(node);
    }
}

void PRender::unregisterEntity(EntityId id)
{
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [&id](Node& node){ return node.id == id; }),
                nodes.end());
}

void PRender::update(int timeStep)
{
    timeSinceLastDraw += timeStep;

    if (timeSinceLastDraw >= timeBetweenDraws)
    {
          timeSinceLastDraw -= timeBetweenDraws;

         for (auto node = nodes.begin();
              node != nodes.end(); ++node)
         {
             sprites.addSprite(node->position->pos.floor(),
                               node->render->getTexCoords(),
                               node->render->getColor());
         }

         rWindow.draw(background);
         rWindow.draw(sprites);
         rWindow.display();

         sprites.clearSprites();
    }
}
