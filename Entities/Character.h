//
// Created by Loïc Coquelet on 23/10/2018.
//

#ifndef PLANTSVSZOMBIES_CHARACTER_H
#define PLANTSVSZOMBIES_CHARACTER_H

#include <string>

#include "../IObservable.h"
#include "AbstractEntity.h"
#include "../GameContext/Lane.h"
#include <SFML/Graphics.hpp>
#include "../Graphics/ImageModel.h"

class Lane;
class ImageModel;

class Character: public AbstractEntity, IObservable
{
protected:
    std::list<IObserver*> observers;
    std::string data;
    double X, Y, speed;
    int life;
    Lane *lane;
    ImageModel *image;
    virtual void NotifyAll();
public:
    Character();
    virtual ~Character() = 0;
    virtual std::string GetData() const;
    virtual void Draw(double, sf::RenderWindow&);
    virtual void GetDamaged(int);
    virtual double GetX() const;
    virtual double GetY() const;
    virtual double GetSpeed() const;
    virtual int GetLife() const;
    virtual void SetX(double);
    virtual void SetY(double);
    virtual void SetImage(ImageModel*);
    virtual ImageModel GetImage();
    virtual void SetSpeed(double);
    virtual void SetLife(int);
    virtual void SetLane(Lane*);
    virtual void AddObserver(IObserver*);
    virtual void RemoveObserver(IObserver*);
    virtual std::string& Serialize();
};


#endif //PLANTSVSZOMBIES_CHARACTER_H
