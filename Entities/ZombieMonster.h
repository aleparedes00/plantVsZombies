//
// Created by Loïc Coquelet on 23/10/2018.
//

#ifndef PLANTSVSZOMBIES_ZOMBIEMONSTER_H
#define PLANTSVSZOMBIES_ZOMBIEMONSTER_H

#include "Character.h"

class ZombieMonster: public Character
{
public:
    ZombieMonster();
    ~ZombieMonster();
    void Update();
    void Draw();
    std::string& Serialize();
};


#endif //PLANTSVSZOMBIES_ZOMBIEMONSTER_H
