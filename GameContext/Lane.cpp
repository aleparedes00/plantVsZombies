//
// Created by Loïc Coquelet on 24/10/2018.
//

#include "Lane.h"
#include <iterator>
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

void Lane::AddEntity(Character *entity) {
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

void Lane::Draw() {
    std::list<Character *>::iterator it;
    for (it = this->gameObjects.begin(); it != this->gameObjects.end(); it++) {
        (*it)->Draw();
    }
}

bool Lane::CheckDefeat() {
    std::list<Character *>::iterator it;
    for (it = this->gameObjects.begin(); it != this->gameObjects.end(); it++) {
        if ((*it)->GetX() <= 0) {
            return true;
        }
    }
    return false;
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

