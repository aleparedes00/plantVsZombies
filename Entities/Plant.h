//
// Created by Loïc Coquelet on 06/11/2018.
//

#ifndef PLANTSVSZOMBIES_PLANT_H
#define PLANTSVSZOMBIES_PLANT_H

#include "Character.h"
#include "../Config.h"
#include "../Graphics/ModelSprite.hh"
#include "../GameContext/Lane.h"

#define RATE_OF_FIRE 2

class Plant : public Character {
private:
    ModelSprite *sprite;
    int nextAttack;
    void Fire();
public:
    Plant();
    ~Plant();
    void Update();
    void Draw(double, sf::RenderWindow&);
};


#endif //PLANTSVSZOMBIES_PLANT_H
