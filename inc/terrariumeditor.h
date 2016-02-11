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

struct TerrariumBlueprint
{
    int width;
    int height;
    int tileSize;
    std::string spriteSheetPath;
    std::string dirtTexturePath;
    sf::Color dirtColor;
    std::map<Vec2i, EntityType> entities;
};

struct CursorInfo
{
    Vec2i position;
    EntityType type;
    bool resizingWindow;
};

void runTerrariumBlueprintEditor(std::string blueprintPath = "NOPATH");

#endif // TERRARIUMEDITOR_H