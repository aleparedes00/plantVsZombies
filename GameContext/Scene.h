//
// Created by Loïc Coquelet on 23/10/2018.
//

#ifndef PLANTSVSZOMBIES_SCENE_H
#define PLANTSVSZOMBIES_SCENE_H

#include <list>
#include <random>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Entities/AbstractEntity.h"
#include "TimeManager.h"
#include "../ISerializable.h"
#include "Lane.h"
#include "Input.h"
#include "../Entities/Player.h"

#define LANE_NUMBER 5
#define WAVE_DURATION 30
#define LANE_WIDTH 450
#define LANE_HEIGHT 50
#define Y_OFFSET_BEFORE_LANE 130

class Player;

class Scene : public IObserver/*: public ISerializable*/ {
private:
    Lane lanes[LANE_NUMBER];
    std::string data;
    unsigned int spawnRate;
    unsigned int entities;
    unsigned int remainingZombies;
    double wave;
    void HandleInput(Input&);
    void SpawnMonster();
    void SpawnSun();
    Player* player;
    bool defeat;
    bool fullLanes;
    std::mt19937 gen; // Generator made from seed
    std::uniform_real_distribution<double> rng; // Generate random numbers from generator
public:
    Scene();

    //Scene(const std::string&);
    ~Scene();

    void Update(Input&);

    void Draw(double, sf::RenderWindow&);

    bool CheckDefeat();

    void Notify(IObservable*);

    void Notify(AbstractEntity*);

    void Notify(Character*);

    const Player* GetPlayer();

    //std::string &Serialize();
};

#endif //PLANTSVSZOMBIES_SCENE_H
