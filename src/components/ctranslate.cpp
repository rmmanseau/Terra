#include "ctranslate.h"

SRC_FACTORY_REGISTER(CTranslate);

bool CTranslate::init(YAML::Node node)
{
    direction = Dir::se;
    velocity = 1;

    return true;
}