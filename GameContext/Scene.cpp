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
#include "Lane.h"
#include "../json.hpp"
#include "TimeManager.h"
#include "../Entities/EntityFactory.h"

#define TIME_BETWEEN_WAVES 10
using json = nlohmann::json;

Scene::Scene() {
    this->data = "scene";
    this->nextZombieSpawn = GameLoop::GetStartedTime();
    this->nextSunSpawn = GameLoop::GetStartedTime();
    this->zombies = 0;
    this->wave = 1;
    this->remainingZombies = 2;
    this->defeat = false;
    std::random_device rd;
    this->gen = std::mt19937(rd());
    this->rng = std::uniform_real_distribution<double>();
    this->player = new Player(this);
    this->fullLanes = false;
    for (int i = 0; i < LANE_NUMBER; i++){
        lanes[i] = new Lane;
        lanes[i]->SetNumber(i);
    }
}

//Scene::Scene(const std::string& serials) {
//    this->lanes = std::list<Lane*>();
//    this->data = "scene";
//    json j = json::parse(serials);
//    j = j["zombies"];
//    MonsterFactory *factory = new MonsterFactory;
//    for (json::iterator it = j.begin(); it != j.end(); it++) {
//        Character *character = factory->Unserialize(*it);
//        if (character)
//            this->AddEntity(character);
//    }
//}

Scene::~Scene() {}

void Scene::Update(Input input) {
    this->HandleInput(input);
    this->player->SetInput(input);
    if (this->wave < (GameLoop::GetStartedTime() / 1000.0) / TIME_BETWEEN_WAVES){
        this->remainingZombies += pow(2, this->wave);
        this->wave++;
        std::cout << "Starting wave : " << this->wave << " with " << std::pow(2, this->wave) << " max zombies" <<std::endl;
    }
    fullLanes = true;
    for (auto &lane : lanes) { // Loop used to check if lanes are full or not
        lane->Update();
        fullLanes = lane->LaneIsFull() && fullLanes;
    }
    if (remainingZombies > 0) {
        SpawnMonster();
    }
    SpawnSun();
    //std::cout << "After Scene update" << std::endl;
}

void Scene::Draw(double leftover, sf::RenderWindow& window) {
    for (auto &lane : lanes) {
        lane->Draw(leftover, window);
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

Player* Scene::GetPlayer(){
    return this->player;
}

void Scene::HandleInput(Input input) {
    double point = std::max((double)((input.GetY() - Y_OFFSET) % CELL_SPACING), 0.0);
    if (point <= CELL_SIZE && input.GetX() > X_OFFSET) {
        int laneNumber = (double)((input.GetY() - Y_OFFSET) / CELL_SPACING);
        if (laneNumber <= LANE_NUMBER){
            lanes[laneNumber]->HandleInput(input);
            if (input.GetType() == Types::RightButtonPressed)
                std::cout << "Letting lane " << laneNumber << " handle input" << std::endl;
        } else if (input.GetType() == Types::RightButtonPressed)
            std::cout << "lane not found : " << laneNumber << std::endl;
    } else if (input.GetType() == Types::RightButtonPressed)
        std::cout << "Point not found or input before X_OFFSET" << std::endl;
}

bool Scene::CheckDefeat() {
    return defeat;
}

void Scene::SpawnMonster() {
    int random_lane = (int)(rng(gen) * 5); // Generate number between 0 and 4 // Generate number between 1 and 100
    if (random_lane < 0 || random_lane > 4)
        std::cout << "Wrong values for Lane : " << random_lane << std::endl;
    else if ((GameLoop::GetStartedTime() / 1000.0) >= this->nextZombieSpawn) {
        Character *zombie = EntityFactory::Create("ZombieMonster");
        zombie->AddObserver(this);
        lanes[random_lane]->AddEntity(zombie);
        nextZombieSpawn = 0.5 + std::min((rng(gen) * (TIME_BETWEEN_WAVES / remainingZombies)), 0.3) + (GameLoop::GetStartedTime() / 1000.0);
        this->zombies++;
        this->remainingZombies--;
        std::cout << "Entities : " << this->zombies << " || Remaining zombies : " << this->remainingZombies << std::endl;
    }
}

void Scene::SpawnSun() {
    int random_lane = (int)(rng(gen) * LANE_NUMBER); // Generate number between 0 and 4
    int random_cell = (int)(rng(gen) * CELL_NUMBER); // Generate number between 0 and 8
    if (!fullLanes && (GameLoop::GetStartedTime() / 1000.0) >= this->nextSunSpawn) {
        while (!lanes[random_lane]->CellEmpty(random_cell)) {
            random_lane = (int)(rng(gen) * LANE_NUMBER); // Generate number between 0 and 4
            random_cell = (int)(rng(gen) * CELL_NUMBER); // Generate number between 0 and 8
        }
        if (random_cell < 0 || random_cell > 8)
            std::cout << "Wrong values for Cell : "  << random_cell << " Lane : " << random_lane << std::endl;
        else if (random_lane < 0 || random_lane > 4)
            std::cout << "Wrong values for Cell : "  << random_cell << " Lane : " << random_lane << std::endl;
        else {
            nextSunSpawn = 0.5 + (rng(gen) * 4) + (GameLoop::GetStartedTime() / 1000.0);
            lanes[random_lane]->CreateSun(random_cell);
        }
    }
}

//std::string &Scene::Serialize() {
//    json j;
//    std::list<std::string> serials = std::list<std::string>();
//    std::list<Lane *>::iterator it;
//    for (it = this->lanes.begin(); it != this->lanes.end(); it++)
//        serials.push_back((*it)->Serialize());
//    j["zombies"] = serials;
//    data = j.dump();
//    return this->data;
//}

