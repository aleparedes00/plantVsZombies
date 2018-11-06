//
// Created by Loïc Coquelet on 06/11/2018.
//

#include "Plant.h"

#include "../GameContext/GameLoop.h"
#include "../GameContext/Scene.h"

#include <iostream>

Plant::Plant()
{
    this->life = 100;
    this->data = "Plant";
    this->speed = 0;
    this->sprite = new ModelSprite(data, this->X, this->Y);
}


Plant::~Plant()
{
    delete this->sprite;
}

void Plant::Update()
{
}

void Plant::Draw(double leftover, sf::RenderWindow &window)
{
    sf::CircleShape circle = sf::CircleShape(CELL_SIZE / 2);
    circle.setFillColor(sf::Color::Green);
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

