#include "globals.h"


std::map<Dir, Vec2i> G_DirVecMap =
{
    {Dir::n  , Vec2i( 0, -1)},
    {Dir::ne , Vec2i( 1, -1)},
    {Dir::e  , Vec2i( 1,  0)},
    {Dir::se , Vec2i( 1,  1)},
    {Dir::s  , Vec2i( 0,  1)},
    {Dir::sw , Vec2i(-1,  1)},
    {Dir::w  , Vec2i(-1,  0)},
    {Dir::nw , Vec2i(-1, -1)}
};

std::unordered_map<std::string, EntityType> G_EntityNameTypeMap =
{
    {"Null", 0},
    {"Reserved", 1},
    {"Empty", 2}
};

std::unordered_map<std::string, std::string> G_Paths;

// int G_TargetCycleTime;

// const EntityType G_EType_Null = 0;
// const EntityType G_EType_Reserved = 1;
// const EntityType G_EType_Empty = 2;

