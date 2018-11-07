//
// Created by Loïc Coquelet on 24/10/2018.
//

#include "Lane.h"
#include <iterator>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Graphics/SpriteFactory.hh"
#include "../json.hpp"
#include "../Entities/Character.h"
#include "../Entities/Player.h"

using json = nlohmann::json;

SpriteFactory *Lane::sunSprite = new SpriteFactory("sun", 0, 0);
sf::RectangleShape Lane::cellShape = sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));

Lane::Lane() {
    this->gameObjects = std::set<Character *>();
    this->data = "Lane";
    cellShape.setOutlineThickness(8.f);
    cellShape.setOutlineColor(sf::Color::Green);
}

Lane::~Lane() {}

void Lane::SetNumber(int number) {
    std::cout << "Received number for lane : " << number << std::endl;
    this->number = number;
}

std::set<Character *> Lane::GetEntities() {
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
    entity->SetLane(this);
    entity->SetY(number * CELL_SPACING + Y_OFFSET);
    this->gameObjects.insert(entity);
}

void Lane::RemoveEntity(Character *entity) {
    if (gameObjects.find(entity) != gameObjects.end()) {
        this->gameObjects.erase(entity);
    } else {
        std::cout << "--- DEBUG : Entity not found in set !" << std::endl;
    }
}

void Lane::Update() {
    for (auto entity : gameObjects) {
        entity->Update();
    }
}

void Lane::Draw(double leftover, sf::RenderWindow &window) {
    for (int i = 0; i < CELL_NUMBER; i++) {
        cellShape.setPosition(i * CELL_SPACING + X_OFFSET, number * CELL_SPACING + Y_OFFSET);
        window.draw(cellShape);
        if (cells[i].sun) {
            Lane::sunSprite->Draw(i * CELL_SPACING + X_OFFSET, number * CELL_SPACING + Y_OFFSET, window);
        }
    }
    std::list<Character *>::iterator it;
    for (auto entity : gameObjects) {
        entity->Draw(leftover, window);
    }
    //std::cout << "Drawing lane : " << number << std::endl;
}


void Lane::HandleInput(Input input) {
    double point = std::max((double)((input.GetX() - X_OFFSET) % CELL_SPACING), 0.0);
    if (point <= CELL_SIZE && input.GetX() > X_OFFSET) {
        int cellNumber = (double)((input.GetX() - X_OFFSET) / CELL_SPACING);
        if (cellNumber < CELL_NUMBER){
            if (CellHasSun(cellNumber) && input.GetType() == Types::LeftButtonPressed) {
                RemoveSun(cellNumber);
                Player::AddSuns();
                std::cout << "Praise the Sun, Cell : " << cellNumber << " || Lane : " << this->number << std::endl;
            } else if (CellEmpty(cellNumber) && input.GetType() == Types::RightButtonPressed){
                Character *plant = Player::GetPlant(cellNumber * CELL_SPACING + X_OFFSET, number * CELL_SPACING + Y_OFFSET);
                if (plant != nullptr) {
                    cells[cellNumber].empty = false;
                    this->AddEntity(plant);
                    plant->SetLane(this);
                    std::cout << "Creating plant ! Cell : " << cellNumber << " || Lane : " << this->number << std::endl;
                }
            }
        }
    }
}

void Lane::CreateSun(int position) {
    cells[position].sun = true;
    cells[position].empty = false;
}

void Lane::RemoveSun(int position) {
    cells[position].sun = false;
    cells[position].empty = true;
}

bool Lane::CellHasSun(int position) {
    if (position < 0 || position >= CELL_NUMBER)
        std::cout << "--- DEBUG SEGFAULT : POSITION = " << position << std::endl;
    return cells[position].sun;
}

bool Lane::CellEmpty(int position) {
    return cells[position].empty;
}

bool Lane::LaneIsFull() {
    bool full = true;
    for (auto &cell : cells){
        full = full && !cell.empty;
        if (!full)
            break;
    }
    return full;
}

int Lane::GetEntitiesNumber() {
    return this->gameObjects.size();
}

int Lane::GetLaneLumber() {
    return this->number;
}

//std::string& Lane::Serialize() {
//    json j;
//    std::list<std::string> serials = std::list<std::string>();
//    std::list<Character*>::iterator it;
//    for (it = this->gameObjects.begin(); it != this->gameObjects.end(); it++)
//        serials.push_back((*it)->Serialize());
//    j["zombies"] = serials;
//    data = j.dump();
//    return this->data;
//}

