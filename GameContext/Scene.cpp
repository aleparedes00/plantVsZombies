//
// Created by Loïc Coquelet on 23/10/2018.
//


#include "Scene.h"
#include <iterator>
#include <iostream>
#include <random>
#include <math.h>
#include <algorithm>
#include "GameLoop.h"
#include "../json.hpp"
#include "../MonsterFactory.h"
#include "../Entities/ZombieMonster.h"
#include "../Entities/Player.h"

#define TIME_BETWEEN_WAVES 5
using json = nlohmann::json;

Scene::Scene() {
    this->data = "scene";
    this->nextZombieSpawn = GameLoop::GetStartedTime();
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
    this->HandleInput(input);
    this->player->SetInput(input);
    if (this->wave < (GameLoop::GetStartedTime() / 1000.0) / TIME_BETWEEN_WAVES){
        this->remainingZombies += pow(2, this->wave);
        this->wave++;
        std::cout << "Starting wave : " << this->wave << " with " << std::pow(2, this->wave) << " max entities" <<std::endl;
    }
    fullLanes = true;
    for (auto &lane : lanes) { // Loop used to check if lanes are full or not
        lane.Update();
        fullLanes = lane.IsFull() && fullLanes;
    }
    if (remainingZombies > 0) {
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
//        std::cout << "Lane number from input : " << laneNumber << std::endl;
//        std::cout << "Input X : " << input.GetX() << " || Input Y : " << input.GetY() << std::endl;
    }
}

bool Scene::CheckDefeat() {
    return defeat;
}

void Scene::SpawnMonster() {
    //int random_lane = (int)(rng(gen) * 5); // Generate number between 0 and 4 // Generate number between 1 and 100
    unsigned int lane_choice = 0;
    unsigned int min_entities = entities;
//    if (spawn < 1 || spawn > 100)
//        std::cout << "Wrong values for Spawn : "  << spawn << " Lane : " << random_lane << std::endl;
//    if (random_lane < 0 || random_lane > 4)
//        std::cout << "Wrong values for Spawn : "  << spawn << " Lane : " << random_lane << std::endl;
    if ((GameLoop::GetStartedTime() / 1000.0) >= this->nextZombieSpawn) {
        std::cout << "Spawning zombie at time : " << GameLoop::GetStartedTime() / 1000.0 << std::endl;
        for (auto lane : lanes) {
            if (lane.GetEntitiesNumber() < min_entities){
                min_entities = lane.GetEntitiesNumber();
                lane_choice = lane.GetLaneLumber();
            }
        }
        ZombieMonster *zombie = new ZombieMonster;
        zombie->AddObserver(this);
        lanes[lane_choice].AddEntity(zombie);
        nextZombieSpawn = 0.2 + std::min((rng(gen) * (TIME_BETWEEN_WAVES / remainingZombies)), 0.3) + (GameLoop::GetStartedTime() / 1000.0);
        std::cout << "Next zombie at time : " << nextZombieSpawn << std::endl;
        this->entities++;
        this->remainingZombies--;
        std::cout << "Entities : " << this->entities << " || Remaining zombies : " << this->remainingZombies << std::endl;
    } else {
        std::cout << "Not spawning zombie at time : " << GameLoop::GetStartedTime() / 1000.0 << " with " << remainingZombies << " remaining zombies " << std::endl;
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
            std::cout << "Wrong values for Cell : "  << random_cell << " Lane : " << random_lane << std::endl;
        if (random_lane < 0 || random_lane > 4)
            std::cout << "Wrong values for Cell : "  << random_cell << " Lane : " << random_lane << std::endl;
        lanes[random_lane].CreateSun(random_cell);
        //std::cout << "Spawning new sun in lane " << random_lane << " at cell " << random_cell << std::endl;
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

