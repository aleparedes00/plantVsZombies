//
// Created by Loïc Coquelet on 23/10/2018.
//


#include "Scene.h"
#include <iterator>
#include <iostream>
#include <random>
#include <math.h>
#include "GameLoop.h"
#include "../json.hpp"
#include "../MonsterFactory.h"
#include "../Entities/ZombieMonster.h"
#include "../Entities/Player.h"

#define TIME_BETWEEN_WAVES 5
#define TIME_BEFORE_SPAWNRATE_INCREASE 5
using json = nlohmann::json;

Scene::Scene() {
    this->data = "scene";
    this->spawnRate = 25;
    this->entities = 0;
    this->wave = 1;
    this->remainingZombies = 2;
    this->defeat = false;
    std::random_device rd;
    this->gen = std::mt19937(rd());
    this->rng = std::uniform_real_distribution<double>();
    this->player = new Player(this);
    this->fullLanes = false;
    for (int i = 0; i < LANE_NUMBER; i++){
        lanes[i].SetNumber(i);
    }
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

void Scene::Update(Input &input) {
//    if ((this->spawnRate + 3) / 5 < (GameLoop::GetStartedTime() / 1000) / TIME_BEFORE_SPAWNRATE_INCREASE){
//        this->spawnRate += 5;
//        std::cout << "SpawnRate increasing ! : " << this->spawnRate << std::endl;
//    }
    this->HandleInput(input);
    this->player->SetInput(input);
    if (this->wave < (GameLoop::GetStartedTime() / 1000.0) / TIME_BETWEEN_WAVES){
        this->remainingZombies += pow(2, this->wave);
        this->wave++;
        std::cout << "Starting wave : " << this->wave << " with " << std::pow(2, this->wave) << " max entities" <<std::endl;
    }
    fullLanes = true;
    for (auto &lane : lanes) {
        lane.Update();
        fullLanes = lane.IsFull() && fullLanes;
    }
    if (this->entities <= remainingZombies) {
        SpawnMonster();
    }
    SpawnSun();
    //std::cout << "After Scene update" << std::endl;
}

void Scene::Draw(double leftover, sf::RenderWindow& window) {
    for (auto &lane : lanes) {
        lane.Draw(leftover, window);
    }
    player->Draw(leftover, window);
    //std::cout << "After Scene Draw" << std::endl;
}

void Scene::Notify(IObservable *iObservable) {
    std::cout << "After Scene iobservable Notify" << std::endl;
}

void Scene::Notify(AbstractEntity *entity) {
    std::cout << "After Scene abstract Notify" << std::endl;
}

void Scene::Notify(Character *character) {
    if (character->GetX() <= 0)
        this->defeat = true;
    std::cout << "After Scene character Notify" << std::endl;
}

const Player* Scene::GetPlayer(){
    return this->player;
}

void Scene::HandleInput(Input &input) {
    unsigned int laneNumber = (input.GetY() - Y_OFFSET_BEFORE_LANE) / LANE_NUMBER;
    if (laneNumber < LANE_NUMBER)
        lanes[laneNumber].HandleInput(input);
    else {
        std::cout << "Lane number from input : " << laneNumber << std::endl;
    }
}

bool Scene::CheckDefeat() {
    return defeat;
}

void Scene::SpawnMonster() {
    int random_lane = (int)(rng(gen) * 5); // Generate number between 0 and 4
    int spawn = 1 + (int)(rng(gen) * 100); // Generate number between 1 and 100
    std::cout << "Spawn : "  << spawn << " Lane : " << random_lane << std::endl;
    if (spawn < 1 || spawn > 100)
        std::cout << "Spawn : "  << spawn << " Lane : " << random_lane << std::endl;
    if (random_lane < 0 || random_lane > 4)
        std::cout << "Spawn : "  << spawn << " Lane : " << random_lane << std::endl;
    if (spawn <= this->spawnRate) {
        std::cout << "Spawning new zombie in lane " << random_lane << std::endl;
        ZombieMonster *zombie = new ZombieMonster;
        zombie->AddObserver(this);
        std::cout << "Just before lane assignation " << random_lane << std::endl;
        lanes[random_lane].AddEntity(zombie);
        this->entities++;
        this->remainingZombies--;
        std::cout << "Entities : " << this->entities << std::endl;
        std::cout << "Remaining zombies : " << this->remainingZombies << std::endl;
    }
}

void Scene::SpawnSun() {
    int random_lane = (int)(rng(gen) * 5); // Generate number between 0 and 4
    int random_cell = (int)(rng(gen) * 9); // Generate number between 0 and 8
    int spawn = 1 + (int)(rng(gen) * 100); // Generate number between 1 and 100
    if (!fullLanes && spawn <= 5) {
        while (lanes[random_lane].HasSun(random_cell)) {
            random_lane = (int)(rng(gen) * 5); // Generate number between 0 and 4
            random_cell = (int)(rng(gen) * 9); // Generate number between 0 and 8
        }
        if (random_cell < 0 || random_cell > 8)
            std::cout << "Cell : "  << random_cell << " Lane : " << random_lane << std::endl;
        if (random_lane < 0 || random_lane > 4)
            std::cout << "Cell : "  << random_cell << " Lane : " << random_lane << std::endl;
        lanes[random_lane].CreateSun(random_cell);
        std::cout << "Spawning new sun in lane " << random_lane << " at cell " << random_cell << std::endl;
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

