//
// Created by Alejandra Paredes on 01/11/2018.
//

#include "../json.hpp"
#include <iostream>
#include "../Config.h"
#include "SpriteFactory.hh"

ImageModel *SpriteFactory::CreateImage(std::string data, float positionX, float positionY) {
    sf::Texture *texture = new sf::Texture();
    sf::Sprite *sprite = new sf::Sprite();
    sprite->setPosition(positionX , positionY);
    if(data == "ZombieMonster") {
        sprite = SetZombieSprite(sprite);
        if (!texture->loadFromFile(ZOMBIE_SPRITE)){
            std::cout << "The zombie image didn't load" << std::endl;
            return nullptr;
        } else {
            std::cout << "Zombie image found" << std::endl;
        }
    }
    else if (data == "sun") {
        sprite = SetSunSprite(sprite);
        if (!texture->loadFromFile(SUN_SPRITE)){
            std::cout << "The sun image didn't load" << std::endl;
            return nullptr;
        } else {
            std::cout << "Sun image found" << std::endl;
        }
        //auto size = this->sprite.getTexture()->getSize();
        //auto scale_x = size.x/LANE_WIDTH;
        //auto scale_y = size.y/LANE_WIDTH;
        //this->sprite.setTexture(texture);
        //this->sprite.setScale(0.07, 0.07);
    } else {
        return nullptr;
    }
    if (sprite != nullptr) {
        std::cout << ">>>> Returning a new image " << std::endl;
        return new ImageModel(sprite, texture);
    }
    return nullptr;
}
// this->CastDoubleToFloat(sprite.getTexture()->getSize().x);
float SpriteFactory::CastDoubleToFloat(double x){
    return static_cast<float>(x);
}

sf::Sprite *SpriteFactory::SetZombieSprite(sf::Sprite *sprite) {
    sprite->setScale(0.104, 0.104);
    std::cout << ">>>> Returning a zombie sprite " << std::endl;
    return sprite;
}

sf::Sprite *SpriteFactory::SetSunSprite(sf::Sprite *sprite){
    //auto size = this->sprite.getTexture()->getSize();
    //auto scale_x = size.x/LANE_WIDTH;
    //auto scale_y = size.y/LANE_WIDTH;
    sprite->setScale(0.07, 0.07);
    std::cout << ">>>> Returning a sun sprite " << std::endl;
    return sprite;
}

