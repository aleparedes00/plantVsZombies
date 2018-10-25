//
// Created by Loïc Coquelet on 23/10/2018.
//


#include "Scene.h"
#include <iterator>
#include <iostream>
#include "../json.hpp"
#include "../MonsterFactory.h"

using json = nlohmann::json;

Scene::Scene() {
    this->data = "scene";
    this->player = new Player;
}

//Scene::Scene(const std::string& serials) {
//    this->lanes = std::list<Lane*>();
//    this->data = "scene";
//    json j = json::parse(serials);
//    j = j["entities"];
//    MonsterFactory *factory = new MonsterFactory;
//    for (json::iterator it = j.begin(); it != j.end(); it++) {
//        Character *character = factory->Unserialize(*it);
//        if (character)
//            this->AddEntity(character);
//    }
//}

Scene::~Scene() {}

void Scene::Update(Input* input) {
    for (auto &lane : lanes) {
        lane.Update();
    }
}

void Scene::Draw(unsigned int leftover) {
    for (auto &lane : lanes) {
        lane.Draw();
    }
}

bool Scene::CheckDefeat() {
    for (auto &lane : lanes) {
        if(lane.CheckDefeat())
            return true;
    }
    return false;
}

const Player* Scene::GetPlayer(){
    return this->player;
}

//std::string &Scene::Serialize() {
//    json j;
//    std::list<std::string> serials = std::list<std::string>();
//    std::list<Lane *>::iterator it;
//    for (it = this->lanes.begin(); it != this->lanes.end(); it++)
//        serials.push_back((*it)->Serialize());
//    j["entities"] = serials;
//    data = j.dump();
//    return this->data;
//}

