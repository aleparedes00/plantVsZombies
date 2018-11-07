//
// Created by Loïc Coquelet on 07/11/2018.
//

#ifndef PLANTSVSZOMBIES_PLANTPROJECTILE_H
#define PLANTSVSZOMBIES_PLANTPROJECTILE_H

#include "Character.h"
#include "../Config.h"

class PlantProjectile : public Character {
public:
    PlantProjectile();
    ~PlantProjectile();
    void Update();
    void Draw(double, sf::RenderWindow&);
};


#endif //PLANTSVSZOMBIES_PLANTPROJECTILE_H
