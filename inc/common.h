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

// Forward Declarations
class Terrarium;
class Grid;
class FactorySys;
class Entity;
class Component;
class Process;

// Id Typedefs
typedef unsigned long EntityId;
typedef unsigned long EntityType;

#endif // COMMON_H
