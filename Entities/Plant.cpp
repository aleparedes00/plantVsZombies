//
// Created by Loïc Coquelet on 06/11/2018.
//

#include "Plant.h"

#include "../GameContext/GameLoop.h"
#include "../GameContext/Scene.h"

#include <iostream>
#include "PlantProjectile.h"

Plant::Plant()
{
    this->life = 100;
    this->data = "Plant";
    this->speed = 0;
    this->sprite = new ModelSprite(data, this->X, this->Y);
    this->nextAttack = RATE_OF_FIRE + GameLoop::GetStartedTime() / 1000;
}


Plant::~Plant()
{
    delete this->sprite;
}

void Plant::Update() {
    this->Fire();
    Character::Update();
}

void Plant::Fire(){
    if ((GameLoop::GetStartedTime() / 1000.0) >= this->nextAttack) {
        Character *projectile = new PlantProjectile();
        projectile->SetX(this->X);
        projectile->SetY(this->Y);
        lane->AddEntity(projectile);
        this->nextAttack = (GameLoop::GetStartedTime() / 1000) + RATE_OF_FIRE;
    }
}

void Plant::Draw(double leftover, sf::RenderWindow &window)
{
    sf::CircleShape circle = sf::CircleShape(CELL_SIZE / 2); // PLACEHOLDER
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(this->X, this->Y);
    window.draw(circle);
    //this->sprite->Draw(this, leftover, window);
}

//std::string& Plant::Serialize()
//{
//    json j;
//    j["name"] = "Plant";
//    j["type"] = "Character";
//    j["Life"] = this->life;
//    j["X"] = this->X;
//    j["Y"] = this->Y;
//    this->data = j.dump();
//    return this->data;
//}

