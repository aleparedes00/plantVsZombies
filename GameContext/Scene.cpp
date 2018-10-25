//
// Created by Loïc Coquelet on 23/10/2018.
//


#include "Scene.h"
#include <iterator>
#include <iostream>
#include "../json.hpp"
#include "../MonsterFactory.h"
#include "GameLoop.h"
#include "../Entities/ZombieMonster.h"

using json = nlohmann::json;

Scene::Scene() {
    this->data = "scene";
    this->player = new Player;
    this->spawnRate = 1;
    this->entities = 0;
    this->wave = 1;
    this->defeat = false;
    std::srand(std::time(nullptr));
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
    if ((this->spawnRate + 3) / 5 < (GameLoop::GetStartedTime() / 1000) / 30){
        this->spawnRate += 5;
        std::cout << "SpawnRate increasing ! : " << this->spawnRate << std::endl;
    }
    if (this->wave < (GameLoop::GetStartedTime() / 1000) / 5){
        std::cout << "Starting wave : " << this->wave << std::endl;
        this->wave++;
    } /*else
        std::cout << "wave : " << this->wave << " time : " << GameLoop::GetStartedTime() << std::endl;*/
    for (auto &lane : lanes) {
        lane.Update();
    }
    if (this->entities <1)//this->entities < (2 ** &(this->wave)))
        SpawnMonster();
    //std::cout << "After Scene update" << std::endl;
}

void Scene::Draw(unsigned int leftover) {
    for (auto &lane : lanes) {
        lane.Draw();
    }
    //std::cout << "After Scene Draw" << std::endl;
}

void Scene::Notify(IObservable* entity) {
    this->defeat = true;
    //std::cout << "After Scene Notify" << std::endl;
}

const Player* Scene::GetPlayer(){
    return this->player;
}

void Scene::HandleInput(Input *) {
    return;
}

bool Scene::CheckDefeat() {
    //std::cout << "After Scene CheckDefeat" << std::endl;
    return defeat;
}

void Scene::SpawnMonster() {
    int random_lane = std::rand()%5; // Generate number between 0 and 4
    int spawn = 1 + (std::rand()%100); // Generate number between 1 and 100
    if (spawn <= this->spawnRate) {
        std::cout << "Spawning new zombie in lane " << random_lane << std::endl;
        ZombieMonster *zombie = new ZombieMonster;
        zombie->AddObserver(this);
        std::cout << "Just before lane assignation " << random_lane << std::endl;
        lanes[random_lane].AddEntity(zombie);
        this->entities++;
        std::cout << "Entities : " << this->entities << std::endl;
    }
    //std::cout << "No spawn : "  << spawn << " SpawnRate : " << this->spawnRate << std::endl;
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

