//
// Created by Loïc Coquelet on 07/11/2018.
//

#include "PlantProjectile.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#define DAMAGE 40

PlantProjectile::PlantProjectile() {
    this->data = "PlantProjectile";
    this->speed = 4;
    this->shape = sf::CircleShape(CELL_SIZE / 4);
    this->shape.setFillColor(sf::Color::Magenta);
}

PlantProjectile::~PlantProjectile() {
}

void PlantProjectile::Update() {
    this->X += this->speed;
    if (this->X > 1000) {
        std::cout << "groooarrr je mourru ! " << this->data << std::endl;
        this->life = -1;
        NotifyAll();
    } else {
        CheckCollision();
    }
}

void PlantProjectile::CheckCollision(){
    std::set<Character*> characters = lane->GetEntities();
    for (auto character : characters){
        if (character->GetData() == "ZombieMonster") {
            if (Intersects(character)) {
                character->GetDamaged(DAMAGE);
                this->life = -1;
                NotifyAll();
                break;
            }
        }
    }
}

void PlantProjectile::Draw(double, sf::RenderWindow &window) {
    this->shape.setPosition(this->X, this->Y);
    window.draw(shape);
}

bool PlantProjectile::Intersects(Character *character) {
    sf::FloatRect hitbox = character->GetImage().GetSprite().getGlobalBounds();
    hitbox.height /= 2;
    return hitbox.intersects(shape.getGlobalBounds());
}