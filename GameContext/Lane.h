//
// Created by Loïc Coquelet on 24/10/2018.
//

#ifndef PLANTSVSZOMBIES_LANE_H
#define PLANTSVSZOMBIES_LANE_H


#include <list>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Entities/Character.h"
#include "../IObserver.h"
#include "Input.h"
#include "../Config.h"
#include "../Graphics/ModelSprite.hh"

struct CELL {
    bool sun = false;
    bool empty = true;
};

class Lane : public IObserver{
private:
    unsigned int number;
    bool full;
    static ModelSprite* sunSprite;
    std::list<Character*> gameObjects;
    std::string data;
    CELL cells[CELL_NUMBER];
    void RemoveEntity(Character*);
    void Notify(IObservable*);
    void Notify(AbstractEntity*);
    void Notify(Character*);
public:
    Lane();
    ~Lane();
    void SetNumber(const unsigned int);
    std::list<Character*> GetEntities() const;
    void AddEntity(Character*);
    void Update();
    void Draw(double, sf::RenderWindow&);
    void HandleInput(Input&);
    void CreateSun(unsigned int);
    bool HasSun(unsigned int);
    bool IsFull();
    unsigned int GetEntitiesNumber();
    unsigned int GetLaneLumber();
};


#endif //PLANTSVSZOMBIES_LANE_H
