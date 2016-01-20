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

std::map<std::string, EntityType> G_EntityNameTypeMap =
{
    {"Null", EntityType::Null},
    {"Empty", EntityType::Empty},
    {"Rock", EntityType::Rock},
    {"Grass", EntityType::Grass},
    {"DumbBug", EntityType::DumbBug}
};
