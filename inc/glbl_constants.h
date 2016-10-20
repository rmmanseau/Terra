#ifndef GLBL_CONSTANTS_H
#define GLBL_CONSTANTS_H

#include "common.h"
#include "vec2.h"

class Constants {
    // std::map<Dir, Vec2i> G_DirVecMap;
    // std::unordered_map<std::string, EntityType> G_EntityNameTypeMap;
    // std::unordered_map<std::string, std::string> G_Paths;
    EntityType m_entityTypeNull;
    EntityType m_entityTypeReserved;
    EntityType m_entityTypeEmpty;
    std::unordered_map<std::string, EntityType> m_entityNameToEntityTypeMap;
    std::unordered_map<EntityType, std::string> m_entityTypeToEntityNameMap;
    int m_targetCycleTime;

public:
    Constants() {}
    void init();

    // Vec2i dirToVec(Dir dir);
    // EntityType eNameToType(std::string name);
    // std::string getPath(std::string);
    int eAmount();
    std::string eName(EntityType type);
    EntityType eType(std::string name);
    EntityType eTypeNull() {return m_entityTypeNull; }
    EntityType eTypeReserved() {return m_entityTypeReserved; }
    EntityType eTypeEmpty() {return m_entityTypeEmpty; }
    int targetCycleTime() {return m_targetCycleTime; }
};

namespace glbl
{
    extern Constants constants;
}

#endif // GLBL_CONSTANTS_H