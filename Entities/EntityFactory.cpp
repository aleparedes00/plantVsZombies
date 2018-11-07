//
// Created by Loïc Coquelet on 07/11/2018.
//

#include "EntityFactory.h"
#include "ZombieMonster.h"
#include "Plant.h"
#include "PlantProjectile.h"

Character* EntityFactory::Create(const std::string& name)
{
    if(name == "ZombieMonster")
        return new ZombieMonster;
    else if(name == "Plant")
        return new Plant;
    else if(name == "PlantProjectile")
        return new PlantProjectile;
    else
        return nullptr;
}