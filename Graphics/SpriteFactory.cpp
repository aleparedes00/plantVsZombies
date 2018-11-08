//
// Created by Alejandra Paredes on 01/11/2018.
//

#include "../json.hpp"
#include <iostream>
#include "../Config.h"
#include "SpriteFactory.hh"

using json = nlohmann::json;

ImageModel *SpriteFactory::CreateImage(std::string data, float positionX, float positionY) {
    sf::Sprite *sprite = new sf::Sprite();
    sprite->setPosition(positionX , positionY);
    if(data == "ZombieMonster") {
        sprite = SetZombieSprite(sprite);
    }
    else if (data == "sun") {
        sprite = SetSunSprite(sprite);
        //auto size = this->sprite.getTexture()->getSize();
        //auto scale_x = size.x/LANE_WIDTH;
        //auto scale_y = size.y/LANE_WIDTH;
        //this->sprite.setTexture(texture);
        //this->sprite.setScale(0.07, 0.07);
    } else {
        return nullptr;
    }
    if (sprite != nullptr)
        return new ImageModel(sprite);
    return nullptr;
}
// this->CastDoubleToFloat(sprite.getTexture()->getSize().x);
float SpriteFactory::CastDoubleToFloat(double x){
    return static_cast<float>(x);
}

sf::Sprite *SpriteFactory::SetZombieSprite(sf::Sprite *sprite) {
    sf::Texture *texture = new sf::Texture();
    if (!texture->loadFromFile(ZOMBIE_SPRITE)){
        throw new std::runtime_error("The image didn't load");
        return nullptr;
    }
    sprite->setTexture(*texture);
    float float_x = CastDoubleToFloat(sprite->getTexture()->getSize().x);
    float float_y = CastDoubleToFloat(sprite->getTexture()->getSize().y);
    sprite->setOrigin(sf::Vector2f(CastDoubleToFloat(float_x * 0.2), CastDoubleToFloat(float_y * 0.2)));
    sprite->setScale(0.104, 0.104);
    return sprite;
}

sf::Sprite *SpriteFactory::SetSunSprite(sf::Sprite *sprite){
    sf::Texture *texture = new sf::Texture();
    if (!texture->loadFromFile(SUN_SPRITE)){
        std::cout << "The image didn't load" << std::endl;
    }
    std::cout << ">>>> Creating a sun sprite " << std::endl;
    //auto size = this->sprite.getTexture()->getSize();
    //auto scale_x = size.x/LANE_WIDTH;
    //auto scale_y = size.y/LANE_WIDTH;
    sprite->setTexture(*texture, true);
    //sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x * 0.2, sprite.getTexture()->getSize().y * 0.2));
    sprite->setScale(0.07, 0.07);
    return sprite;
}

