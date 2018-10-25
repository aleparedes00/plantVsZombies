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

class Scene /*: public ISerializable*/ {
private:
    Lane lanes[LANE_NUMBER];
    std::string data;
    //void HandleInputs(std::list<Input*>);
    void HandleInput(Input*);
    Player* player;
public:
    Scene();

    //Scene(const std::string&);
    ~Scene();

    //void Update(std::list<Input*>);
    void Update(Input*);

    void Draw(unsigned int);

    bool CheckDefeat();

    const Player* GetPlayer();

    //std::string &Serialize();
};

#endif //PLANTSVSZOMBIES_SCENE_H
