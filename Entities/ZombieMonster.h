//
// Created by Loïc Coquelet on 23/10/2018.
//

#ifndef PLANTSVSZOMBIES_ZOMBIEMONSTER_H
#define PLANTSVSZOMBIES_ZOMBIEMONSTER_H

#include "Character.h"
#include "../Graphics/ModelSprite.hh"

class ZombieMonster: public Character
{
private:
    void CheckEndGame();
    ModelSprite *sprite;
public:
    ZombieMonster();
    ~ZombieMonster();
    void Update();
    void Draw(double, sf::RenderWindow&);
    //std::string& Serialize();
};


#endif //PLANTSVSZOMBIES_ZOMBIEMONSTER_H
