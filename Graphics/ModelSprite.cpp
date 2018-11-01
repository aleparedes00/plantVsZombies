//
// Created by Alejandra Paredes on 01/11/2018.
//

#include <json.hpp>
#include <iostream>
#include "ModelSprite.hh"

using json = nlohmann::json;

ModelSprite::ModelSprite(std::string data, float positionX, float positionY) {
    if(data == "ZombieMonster") {
        if (!this->texture.loadFromFile("../Graphics/Resources/Images/zombie2.png")){
            std::cout << "The image didn't load" << std::endl;
        }
        std::cout << ">>>> Creating a sprite type: " << data << std::endl;
        this->sprite.setScale(0.2, 0.2);
        this->sprite.setTexture(texture);
        this->sprite.setPosition(positionX, positionY);

        //TODO où est-ce quón fait le draw()?
    }
}

void ModelSprite::GetTextureInformation(){
    auto size = this->sprite.getTexture()->getSize();
    std::cout << ">>> My sprite size x: " << size.x << std::endl;
    std::cout << ">>> My sprite size y: " << size.y << std::endl;
}

void ModelSprite::SetPosition(float X, float Y) {
    this->sprite.setPosition(X, Y); //TODO check time mananger cast
}

void ModelSprite::Draw(double, sf::RenderWindow &window) {
    window.draw(sprite);
}

