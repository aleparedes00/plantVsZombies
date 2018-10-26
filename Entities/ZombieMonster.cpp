//
// Created by Loïc Coquelet on 23/10/2018.
//


#include "ZombieMonster.h"

#include "../json.hpp"
#include "../GameContext/GameLoop.h"
#include "../GameContext/Scene.h"

#include <iostream>

using json = nlohmann::json;

ZombieMonster::ZombieMonster()
{
    this->life = 100;
    this->data = "ZombieMonster";
    this->X = 500;
}


ZombieMonster::~ZombieMonster()
{
}

void ZombieMonster::Update()
{
    this->X -= 1;
    //std::cout << "groooarrr je suis un zombie ! " << this->X << std::endl;
    if (this->X <= 0)
        this->NotifyAll();
}

void ZombieMonster::Draw()
{

}

std::string& ZombieMonster::Serialize()
{
    json j;
    j["name"] = "ZombieMonster";
    j["type"] = "Character";
    j["Life"] = this->life;
    j["X"] = this->X;
    j["Y"] = this->Y;
    this->data = j.dump();
    return this->data;
}

