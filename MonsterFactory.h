//
// Created by Loïc Coquelet on 23/10/2018.
//

#ifndef PLANTSVSZOMBIES_MONSTERFACTORY_H
#define PLANTSVSZOMBIES_MONSTERFACTORY_H

#include <string>
#include "Entities/Character.h"

class MonsterFactory
{
public:
    Character* Create(const std::string&);
    Character* Unserialize(const std::string&);
};

#endif //PLANTSVSZOMBIES_MONSTERFACTORY_H
