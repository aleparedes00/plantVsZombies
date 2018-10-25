//
// Created by Loïc Coquelet on 23/10/2018.
//

#ifndef PLANTSVSZOMBIES_SCENE_H
#define PLANTSVSZOMBIES_SCENE_H

#include <list>
#include "../Entities/AbstractEntity.h"
#include "TimeManager.h"
#include "../ISerializable.h"
#include "Lane.h"
#include "Input.h"
#include "../Entities/Player.h"

#define LANE_NUMBER 5
#define WAVE_DURATION 30

class Scene : public IObserver/*: public ISerializable*/ {
private:
    Lane lanes[LANE_NUMBER];
    std::string data;
    unsigned int spawnRate;
    unsigned int entities;
    unsigned int wave;
    void HandleInput(Input*);
    void SpawnMonster();
    Player* player;
    bool defeat;
public:
    Scene();

    //Scene(const std::string&);
    ~Scene();

    void Update(Input*);

    void Draw(unsigned int);

    bool CheckDefeat();

    void Notify(IObservable*);

    const Player* GetPlayer();

    //std::string &Serialize();
};

#endif //PLANTSVSZOMBIES_SCENE_H
