//
// Created by Loïc Coquelet on 07/11/2018.
//

#ifndef PLANTSVSZOMBIES_ENTITYFACTORY_H
#define PLANTSVSZOMBIES_ENTITYFACTORY_H


#include <string>
#include "Character.h"

class EntityFactory {
public:
    static Character* Create(const std::string&);
};


#endif //PLANTSVSZOMBIES_ENTITYFACTORY_H
