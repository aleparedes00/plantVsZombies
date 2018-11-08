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
    this->X = 1000;
    this->speed = 1;
    this->sprite = new SpriteFactory(data, this->X, this->Y);
}


ZombieMonster::~ZombieMonster()
{
    delete this->sprite;
}

void ZombieMonster::CheckEndGame() {
    if (this->X <= 0) {
        std::cout << "groooarrr je te mange ! " << this->X << std::endl;
        this->NotifyAll();
    }
}

void ZombieMonster::Update()
{
    this->X -= this->speed;
    //std::cout << "groooarrr je suis un zombie ! " << this->X << std::endl;
    this->CheckEndGame();
}

void ZombieMonster::Draw(double leftover, sf::RenderWindow &window)
{
    this->sprite->Draw(this, leftover, window);
}

//std::string& ZombieMonster::Serialize()
//{
//    json j;
//    j["name"] = "ZombieMonster";
//    j["type"] = "Character";
//    j["Life"] = this->life;
//    j["X"] = this->X;
//    j["Y"] = this->Y;
//    this->data = j.dump();
//    return this->data;
//}

