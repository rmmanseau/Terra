#include "prender.h"

PRender::PRender(sf::RenderWindow& window, int tileSize, const std::string& spriteSheetPath,
                 const std::string& dirtTexturePath, sf::Color dirtColor)
    : rWindow(window)
    , sprites(tileSize, spriteSheetPath)
    , background(window.getSize().x, window.getSize().y, dirtTexturePath, dirtColor)
    , timeBetweenDraws((1./120) * 1000000)
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

        for (auto node = nodes.begin();
        node != nodes.end(); ++node)
        {
            Vec2i pos = node->position->pos.floor();

            for (int i = 0; i < node->render->layers.size(); ++i)
            {
                CRender::Layer& layer = node->render->layers[i];
                sprites.addSprite(pos, layer.texCoords, layer.color);
            }
        }

        rWindow.draw(background);
        rWindow.draw(sprites);
        rWindow.display();

        sprites.clearSprites();
    }
}
