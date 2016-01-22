#include "prender.h"

PRender::PRender(sf::RenderWindow& window, int tileSize, const std::string& spriteSheetPath,
                 const std::string& dirtTexturePath, sf::Color dirtColor)
    : rWindow(window)
    , sprites(tileSize, spriteSheetPath)
    , background(window.getSize().x, window.getSize().y, dirtTexturePath, dirtColor)
    , timeBetweenDraws((1./80) * 1000000)
    , timeSinceLastDraw(0)
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
        std::cout << "DRAWING NOW" << std::endl;


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
