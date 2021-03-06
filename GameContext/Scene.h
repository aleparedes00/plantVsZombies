//
// Created by Loïc Coquelet on 23/10/2018.
//

#ifndef PLANTSVSZOMBIES_SCENE_H
#define PLANTSVSZOMBIES_SCENE_H

#include <list>
#include <random>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../IObserver.h"
#include "../ISerializable.h"
#include "Input.h"
#include "../Entities/Player.h"
#include "../Config.h"

class Player;
class Lane;
class AbstractEntity;

class Scene : public IObserver {
private:
    Lane* lanes[LANE_NUMBER];
    std::string data;
    double nextZombieSpawn;
    double nextSunSpawn;
    unsigned int zombies;
    unsigned int remainingZombies;
    double wave;
    void HandleInput(Input);
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

    void Update(Input);

    void Draw(double, sf::RenderWindow&);

    bool CheckDefeat();

    void Notify(IObservable*);

    void Notify(AbstractEntity*);

    void Notify(Character*);

    Player* GetPlayer();

    void AddEntity(Character*);

    //std::string &Serialize();
};

#endif //PLANTSVSZOMBIES_SCENE_H
