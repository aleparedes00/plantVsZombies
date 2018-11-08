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
#include "Graphics/SpriteFactory.hh"

using json = nlohmann::json;

ImageModel *Lane::sunSprite = SpriteFactory::CreateImage("sun", 0, 0);
sf::RectangleShape Lane::cellShape = sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));

Lane::Lane() {
    std::cout << "Start of lane initialization" << std::endl;
    this->data = "Lane";
    cellShape.setOutlineThickness(8.f);
    cellShape.setOutlineColor(sf::Color::Green);
    std::cout << "End of lane initialization" << std::endl;
}

Lane::~Lane() {}

void Lane::SetNumber(int number) {
    this->number = number;
    std::cout << "Received number for lane : " << number << std::endl;
}

std::set<Character *> Lane::GetEntities() {
    return this->gameObjects;
}

void Lane::Notify(IObservable *observable) {

}

void Lane::Notify(AbstractEntity *entity) {

}

void Lane::Notify(Character *character) {
    if (character->GetLife() <= 0){
        toDelete.insert(character);
    }
}

void Lane::AddEntity(Character *entity) {
    entity->AddObserver(this);
    entity->SetLane(this);
    entity->SetY(number * CELL_SPACING + Y_OFFSET);
    this->gameObjects.insert(entity);
}

void Lane::Update() {
    for (auto entity : gameObjects) {
        entity->Update();
    }
    for (auto entity : toDelete) {
        gameObjects.erase(entity);
    }
    toDelete.clear();
}

void Lane::Draw(double leftover, sf::RenderWindow &window) {
    for (int i = 0; i < CELL_NUMBER; i++) {
        cellShape.setPosition(i * CELL_SPACING + X_OFFSET, number * CELL_SPACING + Y_OFFSET);
        window.draw(cellShape);
        if (cells[i].sun) {
            if (sunSprite!= nullptr)
                Lane::sunSprite->Draw(i * CELL_SPACING + X_OFFSET, number * CELL_SPACING + Y_OFFSET, window);
            else
                std::cout << "SUNSPRITE IS NULL" << number << std::endl;
        }
    }
    std::list<Character *>::iterator it;
    for (auto entity : gameObjects) {
        entity->Draw(leftover, window);
    }
    //std::cout << "Drawing lane : " << number << std::endl;
}


void Lane::HandleInput(Input input) {
    if(InputOnCell(input)) {
        int cellNumber = (double)((input.GetX() - X_OFFSET) / CELL_SPACING);
        if (CellHasSun(cellNumber) && input.GetType() == Types::LeftButtonPressed) {
            CollectSuns(cellNumber);
        } else if (CellEmpty(cellNumber) && input.GetType() == Types::RightButtonPressed){
            CreatePlant(cellNumber);
        }

    }
}

bool Lane::InputOnCell(Input input) {
    bool onCell = false;
    double point = std::max((double)((input.GetX() - X_OFFSET) % CELL_SPACING), 0.0);
    if (point <= CELL_SIZE && input.GetX() > X_OFFSET) {
        int cellNumber = (double)((input.GetX() - X_OFFSET) / CELL_SPACING);
        if (cellNumber < CELL_NUMBER){
            onCell = true;
        }
    }
    return onCell;
}

void Lane::CollectSuns(int cellNumber) {
    RemoveSun(cellNumber);
    Player::AddSuns();
    std::cout << "Praise the Sun, Cell : " << cellNumber << " || Lane : " << this->number << std::endl;
}

void Lane::CreatePlant(int cellNumber) {
    Character *plant = Player::GetPlant(cellNumber * CELL_SPACING + X_OFFSET, number * CELL_SPACING + Y_OFFSET);
    if (plant != nullptr) {
        cells[cellNumber].empty = false;
        this->AddEntity(plant);
        plant->SetLane(this);
    } else {
        std::cout << "Got a nullptr instead of a plant " << std::endl;
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

