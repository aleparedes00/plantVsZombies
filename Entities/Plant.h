//
// Created by Loïc Coquelet on 06/11/2018.
//

#ifndef PLANTSVSZOMBIES_PLANT_H
#define PLANTSVSZOMBIES_PLANT_H

#include "Character.h"
#include "../Graphics/ModelSprite.hh"

class Plant : public Character {
private:
    ModelSprite *sprite;
public:
    Plant();
    ~Plant();
    void Update();
    void Draw(double, sf::RenderWindow&);
};


#endif //PLANTSVSZOMBIES_PLANT_H
