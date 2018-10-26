//
// Created by Loïc Coquelet on 24/10/2018.
//

#include "Lane.h"
#include <iterator>
#include <iostream>
#include "../json.hpp"
#include "../Entities/Character.h"

using json = nlohmann::json;

Lane::Lane() {
    this->gameObjects = std::list<Character *>();
    this->data = "Lane";
}

Lane::~Lane() {}

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
    this->gameObjects.push_back(entity);
    std::cout << "received a new zombie !" << std::endl;
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

void Lane::Draw() {
    std::list<Character *>::iterator it;
    for (it = this->gameObjects.begin(); it != this->gameObjects.end(); it++) {
        (*it)->Draw();
    }
}

bool CheckDefeat() {
    return false;
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

