//
// Created by Loïc Coquelet on 23/10/2018.
//


#include "Scene.h"
#include <iterator>
#include <iostream>
#include <random>
#include <math.h>
#include "../json.hpp"
#include "../MonsterFactory.h"
#include "GameLoop.h"
#include "../Entities/ZombieMonster.h"

#define TIME_BETWEEN_WAVES 5
#define TIME_BEFORE_SPAWNRATE_INCREASE 5
using json = nlohmann::json;

Scene::Scene() {
    this->data = "scene";
    this->player = new Player;
    this->spawnRate = 75;
    this->entities = 0;
    this->wave = 1;
    this->remainingZombies = 2;
    this->defeat = false;
    std::random_device rd;
    this->gen = std::mt19937(rd());
    this->rng = std::uniform_real_distribution<double>();
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
//    if ((this->spawnRate + 3) / 5 < (GameLoop::GetStartedTime() / 1000) / TIME_BEFORE_SPAWNRATE_INCREASE){
//        this->spawnRate += 5;
//        std::cout << "SpawnRate increasing ! : " << this->spawnRate << std::endl;
//    }
    if (this->wave < (GameLoop::GetStartedTime() / 1000.0) / TIME_BETWEEN_WAVES){
        this->remainingZombies += pow(2, this->wave);
        this->wave++;
        std::cout << "Starting wave : " << this->wave << " with " << std::pow(2, this->wave) << " max entities" <<std::endl;
    }
    for (auto &lane : lanes) {
        lane.Update();
    }
    if (this->entities < remainingZombies)
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
    std::cout << "After Scene Notify" << std::endl;
}

const Player* Scene::GetPlayer(){
    return this->player;
}

void Scene::HandleInput(Input *) {
    return;
}

bool Scene::CheckDefeat() {
    return defeat;
}

void Scene::SpawnMonster() {
    int random_lane = (int)(rng(gen) * 5); // Generate number between 0 and 4
    int spawn = 1 + (int)(rng(gen) * 100); // Generate number between 1 and 100
    if (spawn < 1 || spawn > 100)
        std::cout << "Spawn : "  << spawn << " Lane : " << random_lane << std::endl;
    if (random_lane < 0 || random_lane > 4)
        std::cout << "Spawn : "  << spawn << " Lane : " << random_lane << std::endl;
    if (spawn <= this->spawnRate) {
        std::cout << "Spawning new zombie in lane " << random_lane << std::endl;
        ZombieMonster *zombie = new ZombieMonster;
        zombie->SetY(random_lane * 50 + 10);
        zombie->AddObserver(this);
        std::cout << "Just before lane assignation " << random_lane << std::endl;
        lanes[random_lane].AddEntity(zombie);
        this->entities++;
        this->remainingZombies--;
        std::cout << "Entities : " << this->entities << std::endl;
        std::cout << "Remaining zombies : " << this->remainingZombies << std::endl;
    }
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

