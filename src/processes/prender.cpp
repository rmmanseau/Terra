#include "prender.h"

PRender::PRender(sf::RenderWindow& window, int width, int height, int tileSize)
    : background(width*tileSize, height*tileSize,
                 "../assets/textures/dirt.png", sf::Color(133, 87, 35))
    , sprites(tileSize, "../assets/textures/sprite_sheet_8.png")
    , rWindow(window)
{}

PRender::Node::Node(EntityId id, std::weak_ptr<CPosition> position,
                    std::weak_ptr<CRender> render)
    : id(id)
    , invalid(false)
    , position(position)
    , render(render)
{}

void PRender::removeInvalidNodes()
{
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [](Node& node) { return node.invalid; }),
                nodes.end());
}

void PRender::registerEntity(Entity& entity)
{
    std::weak_ptr<CPosition> position = entity.getComponent<CPosition>();
    std::weak_ptr<CRender> render = entity.getComponent<CRender>();

    if (position.lock() && render.lock())
        nodes.push_back(Node(entity.getId(), position, render));
}

void PRender::update()
{
    for (auto itr = nodes.begin();
         itr != nodes.end(); ++itr)
    {
        std::shared_ptr<CPosition> position = itr->position.lock();
        std::shared_ptr<CRender> render = itr->render.lock();
        
        if (position && render)
        {
            sprites.addSprite(position->getPos().floor(),
                              render->getTexCoords(),
                              render->getColor());
        }
        else
        {
            itr->invalid = true;
        }
    }
    removeInvalidNodes();

    rWindow.draw(background);
    rWindow.draw(sprites);
    rWindow.display();

    sprites.clearSprites();
}
