//
// Created by Loïc Coquelet on 24/10/2018.
//

#include "Lane.h"
#include <iterator>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Graphics/SpriteFactory.hh"
#include "../json.hpp"
#include "../Entities/Character.h"

using json = nlohmann::json;

SpriteFactory *Lane::sunSprite = new SpriteFactory("sun", 0, 0);

Lane::Lane() {
    this->gameObjects = std::list<Character *>();
    this->data = "Lane";
}

Lane::~Lane() {}

void Lane::SetNumber(const unsigned int number) {
    std::cout << "Received number for lane : " << number << std::endl;
    this->number = number;
}

std::list<Character *> Lane::GetEntities() const {
    return this->gameObjects;
}

void Lane::Notify(IObservable *observable) {

}

void Lane::Notify(AbstractEntity *entity) {

}

void Lane::Notify(Character *character) {
    if (character->GetLife() <= 0)
        this->RemoveEntity(character);
}

void Lane::AddEntity(Character *entity) {
    entity->AddObserver(this);
    entity->SetY(number * 80 + Y_OFFSET);
    this->gameObjects.push_back(entity);
}

void Lane::RemoveEntity(Character *entity) {
    this->gameObjects.remove(entity);
}

void Lane::Update() {
    std::list<Character *>::iterator it;
    for (it = this->gameObjects.begin(); it != this->gameObjects.end(); it++) {
        (*it)->Update();
    }
}

void Lane::Draw(double leftover, sf::RenderWindow &window) {
    for (int i = 0; i < CELL_NUMBER; i++) {
        sf::RectangleShape rectangle(sf::Vector2f(50.f, 50.f)); // TEMPORARY, need merging !
        rectangle.setOutlineThickness(8.f);
        rectangle.setOutlineColor(sf::Color::Green);
        rectangle.setPosition(i * 80 + 20, number * 80 + Y_OFFSET);
        window.draw(rectangle);
        if (cells[i].sun) {
            Lane::sunSprite->Draw(i * 80 + 20, number * 80 + Y_OFFSET, window);
        }
    }
    std::list<Character *>::iterator it;
    for (it = this->gameObjects.begin(); it != this->gameObjects.end(); it++) {
        (*it)->Draw(leftover, window);
    }
    //std::cout << "Drawing lane : " << number << std::endl;
}


void Lane::HandleInput(Input &input) {
    unsigned int cellNumber = (input.GetX() - X_OFFSET) / CELL_NUMBER;
    if (cellNumber < CELL_NUMBER){
        cells[cellNumber].sun = false;
        cells[cellNumber].empty = true;
    } else {
        std::cout << "Cell number from input : " << cellNumber << std::endl;
    }
}

void Lane::CreateSun(unsigned int position) {
    cells[position].sun = true;
    cells[position].empty = false;
}

bool Lane::HasSun(unsigned int position) {
    return cells[position].sun;
}

bool Lane::IsFull() {
    bool full = true;
    for (auto &cell : cells){
        full = full && !cell.empty;
        if (!full)
            break;
    }
    return full;
}

unsigned int Lane::GetEntitiesNumber() {
    return this->gameObjects.size();
}

unsigned int Lane::GetLaneLumber() {
    return this->number;
}

//std::string& Lane::Serialize() {
//    json j;
//    std::list<std::string> serials = std::list<std::string>();
//    std::list<Character*>::iterator it;
//    for (it = this->gameObjects.begin(); it != this->gameObjects.end(); it++)
//        serials.push_back((*it)->Serialize());
//    j["entities"] = serials;
//    data = j.dump();
//    return this->data;
//}

