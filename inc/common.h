#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <stdexcept>

// Enums
enum class Dir
{
    n,
    ne,
    e,
    se,
    s,
    sw,
    w,
    nw
};

enum class EntityType
{
    Null,
    Reserved,
    Empty,
    Rock,
    Grass,
    DumbBug,
    DumbBugEgg
};

// Forward Declarations
class Terrarium;
class Grid;
class FactorySys;
class Entity;
class Component;
class Process;

// Id Typedefs
typedef unsigned long EntityId;

// Map Typedefs
typedef std::vector<std::shared_ptr<Process> > ProcessVec;
typedef std::unordered_map<EntityId, Entity> EntityMap;
typedef std::unordered_map<std::type_index, std::shared_ptr<Component> > ComponentMap;

#endif // COMMON_H