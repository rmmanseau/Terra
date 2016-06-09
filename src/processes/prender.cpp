#include "prender.h"

PRender::PRender(sf::RenderWindow& window, int tileSize, const std::string& spriteSheetPath,
                 const std::string& dirtTexturePath, sf::Color dirtColor)
    : rWindow(window)
    , timeBetweenDraws((1./60) * 1000000)
    , timeSinceLastDraw(0)
    , draw(false)
    , drawThreadRunning(true)
    , drawThreadFinished(false)
    , drawThread(&PRender::drawFunc, this)
{
    sprites.init(tileSize, spriteSheetPath);
    background.init(window.getSize().x, window.getSize().y, dirtTexturePath, dirtColor);
    window.setActive(false);
}

PRender::~PRender()
{
    drawThreadRunning = false;
    drawThread.join();
}

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

// Seperate Thread
void PRender::drawFunc()
{
    rWindow.setActive(true);

    while(drawThreadRunning)
    {
        if (draw)
        {
            draw = false;

            rWindow.draw(background);

            {
                std::lock_guard<std::mutex> guard(drawMutex);
                rWindow.draw(sprites);
            }

            rWindow.display();
        }
        else
        {
            sf::sleep(sf::microseconds(10));
        }
    }
}

void PRender::update(int timeStep)
{
    sf::Clock timer;

    timeSinceLastDraw += timeStep;
    if (timeSinceLastDraw >= timeBetweenDraws)
    {
        std::cout << "*";

        timeSinceLastDraw = 0;

        std::lock_guard<std::mutex> guard(drawMutex);
        
        sprites.clearSprites();
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

        draw = true;
    }
    std::cout << "PRender:\t" << timer.restart().asMicroseconds() << std::endl;
}
