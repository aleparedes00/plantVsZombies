//
// Created by Loïc Coquelet on 23/10/2018.
//


#include "ZombieMonster.h"

#include "../json.hpp"
#include "../GameContext/GameLoop.h"

using json = nlohmann::json;

ZombieMonster::ZombieMonster()
{
    this->life = 100;
    this->data = "ZombieMonster";
}


ZombieMonster::~ZombieMonster()
{
}

void ZombieMonster::Update()
{
    this->X += (double)GameLoop::GetElapsedTime() / 1000;
    this->Y += (double)GameLoop::GetElapsedTime() / 1000;
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

