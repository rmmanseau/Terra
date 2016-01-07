#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <typeindex>

// Enums
enum class Dir
{
    none,
    n,
    ne,
    e,
    se,
    s,
    sw,
    w,
    nw
};

// Forward Declarations
class Terrarium;
class Grid;
class RenderSys;
class FactorySys;
class Actor;
class Component;
class Process;

// Id Typedefs
typedef unsigned long ActorId;
typedef std::string ComponentId;

// Map Typedefs
typedef std::vector<std::shared_ptr<Process> > ProcessVec;
typedef std::unordered_map<ActorId, Actor> ActorMap;
typedef std::unordered_map<std::type_index, std::shared_ptr<Component> > ComponentMap;
typedef std::unordered_map<std::string, sf::Texture> TextureMap;

#endif // COMMON_H