//
// Created by Alejandra Paredes on 01/11/2018.
//

#include "../json.hpp"
#include <iostream>
#include "../Config.h"
#include "ModelSprite.hh"

using json = nlohmann::json;

ModelSprite::ModelSprite(std::string data, float positionX, float positionY) {
    if(data == "ZombieMonster") {
        if (!this->texture.loadFromFile(ZOMBIE_SPRITE)){
            std::cout << "The zombie image didn't load" << std::endl;
        }
        //auto size = this->sprite.getTexture()->getSize();
        //auto scale_x = size.x/LANE_WIDTH; //TODO ça pete. Check writes and dinamic allocation
        //auto scale_y = size.y/LANE_WIDTH; //TODO Zombie doesn't touche the top if the rectangle
        this->sprite.setTexture(texture);
        this->sprite.setScale(0.104, 0.104);
        this->sprite.setPosition(positionX , positionY);

    }
    else if (data == "sun") {
        if (!this->texture.loadFromFile(SUN_SPRITE)){
            std::cout << "The sun image didn't load" << std::endl;
        }
        //auto size = this->sprite.getTexture()->getSize();
        //auto scale_x = size.x/LANE_WIDTH;
        //auto scale_y = size.y/LANE_WIDTH;
        this->sprite.setTexture(texture);
        this->sprite.setScale(0.07, 0.07);
        this->sprite.setPosition(positionX , positionY);
    }
}

ModelSprite::~ModelSprite() {}

void ModelSprite::Draw(float positionX, float positionY, sf::RenderWindow &window) {
    this->sprite.setPosition(positionX , positionY);
    window.draw(sprite);
}

void ModelSprite::Draw(Character *character, double leftover, sf::RenderWindow &window) {
    this->sprite.setPosition(character->GetX() + (character->GetSpeed() * leftover), character->GetY());
    window.draw(sprite);
}

