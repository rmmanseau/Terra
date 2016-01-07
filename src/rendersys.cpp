#include "rendersys.h"

#include <iostream>
#include <boost/filesystem.hpp>

void RenderSys::loadTextures(std::string path)
{
    namespace fs = boost::filesystem;
    
    fs::path spritePath(path);

    if (!fs::exists(spritePath))
    {
        std::cout << "Couldn't find sprite directory" << std::endl;
        std::cout << spritePath << std::endl;
        return;
    }

    fs::directory_iterator end;
    for (fs::directory_iterator itr(spritePath);
         itr != end;
         ++itr)
    {
        if (fs::is_regular_file(itr->status()))
        {
            std::string texName = itr->path().filename().string();
            texName = texName.substr(0, texName.size()-4); // removes .png
            std::string texPath = itr->path().string();
            sf::Texture tex;

            tex.loadFromFile(texPath);
            textures.insert({texName, tex});
            std::cout << "found: " << texName << std::endl;
        }
    }
}

void RenderSys::init(int w, int h, int size)
{
    tileSize = size;

    loadTextures("../assets/sprites");
    textures["dirt"].setRepeated(true);

    dirtSprite.setTexture(textures["dirt"]);
    dirtSprite.setTextureRect(sf::IntRect(0, 0, w*tileSize, h*tileSize));
    dirtSprite.setColor(sf::Color(133, 87, 35));

    window.create(sf::VideoMode(w*tileSize, h*tileSize, 32),
                  "Terra",
                  sf::Style::Close);
    
    window.draw(dirtSprite);
    window.display();
}

void RenderSys::update(ActorMap& actors)
{
    window.draw(dirtSprite);

    auto end = actors.end();
    for (auto itr = actors.begin(); itr != end; ++itr)
    {
        Actor& current = itr->second;
        std::shared_ptr<CPosition> pos = current.getComponent<CPosition>().lock();
        std::shared_ptr<CRender> render = current.getComponent<CRender>().lock();
        
        if (pos && render)
        {
            render->setSpritePos(pos->getPos()*tileSize);
            window.draw(render->getSprite());
        }
    }

    window.display();
}

sf::Texture& RenderSys::getTexture(std::string texName)
{
    auto itr = textures.find(texName);
    if (itr != textures.end()) {
        return textures[texName];
    }
    else {
        std::cout << "Couldn't find a texture called: " << texName << std::endl;
        return textures["error"];
    }
}
