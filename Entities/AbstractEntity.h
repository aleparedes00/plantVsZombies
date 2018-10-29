//
// Created by Loïc Coquelet on 23/10/2018.
//

#ifndef PLANTSVSZOMBIES_ABSTRACTENTITY_H
#define PLANTSVSZOMBIES_ABSTRACTENTITY_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "../ISerializable.h"

class AbstractEntity : public ISerializable
{
public:
    AbstractEntity();
    virtual ~AbstractEntity() = 0;
    virtual void Update() = 0;
    virtual void Draw(double, sf::RenderWindow&) = 0;
};

#endif //PLANTSVSZOMBIES_ABSTRACTENTITY_H
