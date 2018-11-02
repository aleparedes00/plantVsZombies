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
    this->speed = 1;
    this->sprite = new ModelSprite(data, this->X, this->Y);
}


ZombieMonster::~ZombieMonster()
{
    //delete this->sprite;
}

void ZombieMonster::CheckDeath() {
    if (this->life <= 0) {
        std::cout << "groooarrr je mourru ! " << this->life << std::endl;
        this->NotifyAll();
    }
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
    this->CheckDeath();
    this->CheckEndGame();
}

void ZombieMonster::Draw(double leftover, sf::RenderWindow &window)
{
    this->sprite->SetPosition((this->X - (speed * leftover)), this->Y); //TODO I need float, this is double, Is that safe?
//    sf::RectangleShape rectangle(sf::Vector2f(20.f, 20.f)); // TEMPORARY, need merging !
//    rectangle.setOutlineThickness(5.f);
//    rectangle.setOutlineColor(sf::Color(255, 0, 0));
//    rectangle.setPosition((this->X - (speed * leftover)), this->Y);
//    std::cout << "position x : " << rectangle.getPosition().x << std::endl;
//    std::cout << "position y : " << rectangle.getPosition().y << std::endl;
//    window.draw(rectangle);
    this->sprite->Draw(leftover, window);
    // this->Model.draw(this, leftover, window); // this -> gives position / leftover -> time before next update / window -> to draw
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

