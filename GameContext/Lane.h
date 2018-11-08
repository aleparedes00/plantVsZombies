//
// Created by Loïc Coquelet on 24/10/2018.
//

#ifndef PLANTSVSZOMBIES_LANE_H
#define PLANTSVSZOMBIES_LANE_H


#include "../IObserver.h"
#include <set>
#include <SFML/Graphics.hpp>
#include "../Entities/Character.h"
#include "Input.h"
#include "../Config.h"
#include "../Graphics/ImageModel.h"

class ImageModel;

struct CELL {
    bool sun = false;
    bool empty = true;
};

class Lane : public IObserver{
private:
    int number;
    bool full;
    static ImageModel* sunSprite;
    static sf::RectangleShape cellShape;
    std::set<Character*> gameObjects;
    std::string data;
    CELL cells[CELL_NUMBER];
    void RemoveEntity(Character*);
    void Notify(IObservable*);
    void Notify(AbstractEntity*);
    void Notify(Character*);
public:
    Lane();
    ~Lane();
    void SetNumber(int);
    std::set<Character*> GetEntities();
    void AddEntity(Character*);
    void Update();
    void Draw(double, sf::RenderWindow&);
    void HandleInput(Input);
    void CreateSun(int);
    void RemoveSun(int);
    bool CellHasSun(int);
    bool CellEmpty(int);
    bool LaneIsFull();
    int GetEntitiesNumber();
    int GetLaneLumber();
};


#endif //PLANTSVSZOMBIES_LANE_H
