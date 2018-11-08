//
// Created by Alejandra Paredes on 01/11/2018.
//

#include "../json.hpp"
#include <iostream>
#include "../Config.h"
#include "SpriteFactory.hh"

using json = nlohmann::json;

SpriteFactory::SpriteFactory(std::string data, float positionX, float positionY) {
    this->type = data;
    if(data == "ZombieMonster") {
        if (!this->texture.loadFromFile(ZOMBIE_SPRITE)){
            throw new std::runtime_error("The image didn't load");
        }
        this->sprite.setTexture(texture);
        float float_x = this->CastToFloat(sprite.getTexture()->getSize().x);
        float float_y = this->CastToFloat(sprite.getTexture()->getSize().y);
        sprite.setOrigin(sf::Vector2f((float_x * 0.2), (float_y * 0.2)));
        this->sprite.setScale(0.104, 0.104);
        this->sprite.setPosition(positionX , positionY);

    }
    else if (data == "sun") {
        this->SetSprite(SUN_SPRITE);
        //auto size = this->sprite.getTexture()->getSize();
        //auto scale_x = size.x/LANE_WIDTH;
        //auto scale_y = size.y/LANE_WIDTH;
        //this->sprite.setTexture(texture);
        //this->sprite.setScale(0.07, 0.07);
        this->sprite.setPosition(positionX , positionY);
    }
}
// this->CastToFloat(sprite.getTexture()->getSize().x);
float SpriteFactory::CastToFloat(double x){
    return static_cast<float>(x);
}

void SpriteFactory::SetSprite(std::string file){

    if (!this->texture.loadFromFile(file)){
        std::cout << "The image didn't load" << std::endl;
    }
    std::cout << ">>>> Creating a sprite type: " << this->type << std::endl;
    //auto size = this->sprite.getTexture()->getSize();
    //auto scale_x = size.x/LANE_WIDTH;
    //auto scale_y = size.y/LANE_WIDTH;
    this->sprite.setTexture(texture, true);
    sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x * 0.2, sprite.getTexture()->getSize().y * 0.2));
    this->sprite.setScale(0.07, 0.07);
}

SpriteFactory::~SpriteFactory() {}

void SpriteFactory::Draw(float positionX, float positionY, sf::RenderWindow &window) {
    this->sprite.setPosition(positionX , positionY);
    window.draw(sprite);
}

void SpriteFactory::Draw(Character *character, double leftover, sf::RenderWindow &window) {
    this->sprite.setPosition(character->GetX() + (character->GetSpeed() * leftover), character->GetY());
    window.draw(sprite);
}

