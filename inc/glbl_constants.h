#ifndef GLBL_CONSTANTS_H
#define GLBL_CONSTANTS_H

#include "common.h"
#include "vec2.h"

class Constants {
    // std::map<Dir, Vec2i> G_DirVecMap;
    // std::unordered_map<std::string, EntityType> G_EntityNameTypeMap;
    // std::unordered_map<std::string, std::string> G_Paths;
    EntityType m_eTypeNull;
    EntityType m_eTypeReserved;
    EntityType m_eTypeEmpty;
    int m_targetCycleTime;

public:
    Constants() {}
    void init();

    // Vec2i dirToVec(Dir dir);
    // EntityType eNameToType(std::string name);
    // std::string getPath(std::string);
    EntityType eTypeNull() {return m_eTypeNull; }
    EntityType eTypeReserved() {return m_eTypeReserved; }
    EntityType eTypeEmpty() {return m_eTypeEmpty; }
    int targetCycleTime() {return m_targetCycleTime; }
};

namespace glbl
{
    extern Constants constants;
}

#endif // GLBL_CONSTANTS_H