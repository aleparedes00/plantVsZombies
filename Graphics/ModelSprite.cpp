//
// Created by Alejandra Paredes on 01/11/2018.
//

#include <json.hpp>
#include <iostream>
#include <Config.h>
#include "ModelSprite.hh"

using json = nlohmann::json;

ModelSprite::ModelSprite(std::string data, float positionX, float positionY) {
    this->type = data;
    if(data == "ZombieMonster") {
        if (!this->texture.loadFromFile(ZOMBIE_FILE)){
            throw new std::runtime_error("The image didn't load");
        }
        //std::cout << ">>>> Creating a sprite type: " << data << std::endl;
        this->sprite.setTexture(texture);
        auto size = this->sprite.getTexture()->getSize();
        auto scale_x = size.x/LANE_WIDTH; //TODO ça pete. Check writes and dinamic allocation
        auto scale_y = size.y/LANE_WIDTH; //TODO Zombie doesn't touche the top if the rectangle
        sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x * 0.2, sprite.getTexture()->getSize().y * 0.2));
        this->sprite.setScale(0.104, 0.104);
        this->sprite.setPosition(positionX , positionY);

    }
    else if (data == "sun") {
        this->SetSprite(SUN_FILE);
        this->sprite.setPosition(positionX , positionY);
    }
}

void ModelSprite::SetSprite(std::string file){

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
void ModelSprite::SetPosition(float X, float Y) {
    this->sprite.setPosition(X, Y); //TODO check time mananger cast
}

void ModelSprite::Draw(double, sf::RenderWindow &window) {
    window.draw(sprite);
}

