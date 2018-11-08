//
// Created by Loïc Coquelet on 08/11/2018.
//

#include "ImageModel.h"
#include <iostream>
#include "../Config.h"
#include <SFML/Graphics/RenderWindow.hpp>

ImageModel::ImageModel(sf::Sprite *sprite, sf::Texture *texture) {
    this->sprite = sprite;
    this->texture = texture;
    this->sprite->setTexture(*texture);
    //this->sprite->setOrigin(sf::Vector2f(texture->getSize().x * 0.2, texture->getSize().y * 0.2));
}

ImageModel::~ImageModel() {}

void ImageModel::Draw(float positionX, float positionY, sf::RenderWindow &window) {
    this->sprite->setPosition(positionX , positionY);
    window.draw(*sprite);
}

void ImageModel::Draw(Character *character, double leftover, sf::RenderWindow &window) {
    this->sprite->setPosition(character->GetX() + (character->GetSpeed() * leftover), character->GetY());
    window.draw(*sprite);
}