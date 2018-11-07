//
// Created by Loïc Coquelet on 07/11/2018.
//

#include "PlantProjectile.h"
#include <SFML/Graphics.hpp>
#include <iostream>

PlantProjectile::PlantProjectile() {
    this->data = "PlantProjectile";
    this->speed = 4;
}

PlantProjectile::~PlantProjectile() {
}

void PlantProjectile::Update() {
    this->X += this->speed;
    if (this->X > 1000) {
        this->life = -1;
        NotifyAll();
    }
}

void PlantProjectile::Draw(double, sf::RenderWindow &window) {
    sf::CircleShape circle = sf::CircleShape(CELL_SIZE / 4);
    circle.setFillColor(sf::Color::Magenta);
    circle.setPosition(this->X, this->Y);
    window.draw(circle);
}