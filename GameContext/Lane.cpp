//
// Created by Loïc Coquelet on 24/10/2018.
//

#include "Lane.h"
#include <iterator>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../json.hpp"
#include "../Entities/Character.h"

using json = nlohmann::json;

Lane::Lane() {
    this->gameObjects = std::list<Character *>();
    this->data = "Lane";
}

Lane::~Lane() {}

void Lane::SetNumber(const unsigned int number) {
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

}

void Lane::AddEntity(Character *entity) {
    entity->AddObserver(this);
    entity->SetY(number * 50 + Y_OFFSET);
    this->gameObjects.push_back(entity);
    std::cout << "received a new zombie !" << std::endl;
}

void Lane::RemoveEntity(Character *entity) {
    this->gameObjects.remove(entity);
}

void Lane::Update(Input &input) {
    std::list<Character *>::iterator it;
    for (it = this->gameObjects.begin(); it != this->gameObjects.end(); it++) {
        (*it)->Update();
    }
}

void Lane::Draw(double leftover, sf::RenderWindow &window) {
    for (int i = 0; i < TILE_NUMBER; i++) {
        sf::RectangleShape rectangle(sf::Vector2f(30.f, 30.f)); // TEMPORARY, need merging !
        rectangle.setOutlineThickness(5.f);
        rectangle.setOutlineColor(sf::Color::Green);
        rectangle.setPosition(i * 50 + 20, number * 50 + Y_OFFSET);
//    std::cout << "position x : " << rectangle.getPosition().x << std::endl;
//    std::cout << "position y : " << rectangle.getPosition().y << std::endl;
        window.draw(rectangle);
        if (cells[i].sun) {
            sf::CircleShape circle(15.f); // TEMPORARY, need merging !
            circle.setOutlineThickness(5.f);
            circle.setOutlineColor(sf::Color::Yellow);
            circle.setPosition(i * 50 + 20, number * 50 + Y_OFFSET);
//          std::cout << "position x : " << rectangle.getPosition().x << std::endl;
//          std::cout << "position y : " << rectangle.getPosition().y << std::endl;
            window.draw(circle);
        }
    }
    std::list<Character *>::iterator it;
    for (it = this->gameObjects.begin(); it != this->gameObjects.end(); it++) {
        (*it)->Draw(leftover, window);
    }
}

void Lane::CreateSun(unsigned int position) {
    cells[position].sun = true;
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

