//
// Created by Loïc Coquelet on 24/10/2018.
//

#ifndef PLANTSVSZOMBIES_LANE_H
#define PLANTSVSZOMBIES_LANE_H


#include <list>
#include "../Entities/Character.h"
#include "../IObserver.h"

class Lane : public IObserver{
private:
    std::list<Character*> gameObjects;
    std::string data;
    void RemoveEntity(Character*);
    void Notify(IObservable*);
    void Notify(AbstractEntity*);
    void Notify(Character*);
public:
    Lane();
    ~Lane();
    std::list<Character*> GetEntities() const;
    void AddEntity(Character*);
    void Update();
    void Draw();
};


#endif //PLANTSVSZOMBIES_LANE_H
