//
// Created by Loïc Coquelet on 24/10/2018.
//

#ifndef PLANTSVSZOMBIES_LANE_H
#define PLANTSVSZOMBIES_LANE_H


#include <list>
#include "../Entities/Character.h"

class Lane {
private:
    std::list<Character*> gameObjects;
    std::string data;
public:
    Lane();
    ~Lane();
    std::list<Character*> GetEntities() const;
    void AddEntity(Character*);
    void RemoveEntity(Character*);
    void Update();
    void Draw();
};


#endif //PLANTSVSZOMBIES_LANE_H
