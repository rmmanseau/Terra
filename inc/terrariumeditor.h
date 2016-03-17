#ifndef TERRARIUMEDITOR_H
#define TERRARIUMEDITOR_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "yaml-cpp/yaml.h"

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>

#include "globals.h"
#include "helpers.h"
#include "vec2.h"
#include "background.h"
#include "spritemap.h"
#include "crender.h"

class TerrariumEditor
{
    enum class State
    {
        idle,
        resizing,
        drawing,
        erasing
    };

    struct Blueprint
    {
        int width;
        int height;
        int tileSize;
        std::string spriteSheetPath;
        std::string dirtTexturePath;
        sf::Color dirtColor;
        std::map<Vec2i, EntityType> entities;
    };

    struct Cursor
    {
        Vec2i previousPosition;
        Vec2i position;
        EntityType type;
        bool resizingWindow;
    };

    State state;
    std::unordered_map<int, CRender> renderComponents;
    SpriteMap spriteMap;

    void addCursorToSpriteMap();
    void addEntitiesToSpriteMap();
    
    void changeCursorType(int change);
    void setState(State newState);
    void placeEntityAtCursor();
    void removeEntityAtCursor();


public:
    
    Blueprint blueprint;
    Cursor cursor;
    Background background;

    TerrariumEditor(const std::string& blueprintPath, const std::string& entityBlueprintsPath);

    void loadBlueprint(const std::string& blueprintPath);
    void saveBlueprint(const std::string& blueprintName);
    void loadRenderComponents(const std::string& renderComponentsPath);

    void updateSpriteMap();
    void drawBlueprint(sf::RenderWindow& window);
    void resize(Vec2i delta, sf::RenderWindow& window);


    void update(sf::RenderWindow& window, sf::Event& event);
};

void runTerrariumBlueprintEditor(std::string blueprintPath = "NOPATH");

#endif // TERRARIUMEDITOR_H
