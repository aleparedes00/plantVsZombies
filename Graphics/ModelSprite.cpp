//
// Created by Alejandra Paredes on 01/11/2018.
//

#include <json.hpp>
#include <iostream>
#include <Config.h>
#include "ModelSprite.hh"

using json = nlohmann::json;

ModelSprite::ModelSprite(std::string data, float positionX, float positionY) {
    if(data == "ZombieMonster") {
        if (!this->texture.loadFromFile(ZOMBIE_FILE)){
            std::cout << "The image didn't load" << std::endl;
        }
        std::cout << ">>>> Creating a sprite type: " << data << std::endl;
        //auto size = this->sprite.getTexture()->getSize();
        //auto scale_x = size.x/LANE_WIDTH; //TODO ça pete. Check writes and dinamic allocation
        //auto scale_y = size.y/LANE_WIDTH; //TODO Zombie doesn't touche the top if the rectangle
        this->sprite.setTexture(texture);
        this->sprite.setScale(0.104, 0.104);
        this->sprite.setPosition(positionX , positionY);

    }
    else if (data == "sun") {
        if (!this->texture.loadFromFile("../Graphics/Resources/Images/sun.png")){
            std::cout << "The image didn't load" << std::endl;
        }
        std::cout << ">>>> Creating a sprite type: " << data << std::endl;
        //auto size = this->sprite.getTexture()->getSize();
        //auto scale_x = size.x/LANE_WIDTH;
        //auto scale_y = size.y/LANE_WIDTH;
        this->sprite.setTexture(texture);
        this->sprite.setScale(0.07, 0.07);
        this->sprite.setPosition(positionX , positionY);
    }
}

void ModelSprite::SetPosition(float X, float Y) {
    this->sprite.setPosition(X, Y); //TODO check time mananger cast
}

void ModelSprite::Draw(double, sf::RenderWindow &window) {
    window.draw(sprite);
}

