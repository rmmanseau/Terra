#ifndef GLOBALS_H
#define GLOBALS_H

#include "common.h"
#include "vec2.h"

extern std::map<Dir, Vec2i> G_DirVecMap;
extern std::unordered_map<std::string, EntityType> G_EntityNameTypeMap;
extern const EntityType G_EType_Null;
extern const EntityType G_EType_Reserved;
extern const EntityType G_EType_Empty;

#endif // GLOBALS_H
