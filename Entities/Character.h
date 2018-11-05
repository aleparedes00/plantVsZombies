//
// Created by Loïc Coquelet on 23/10/2018.
//

#ifndef PLANTSVSZOMBIES_CHARACTER_H
#define PLANTSVSZOMBIES_CHARACTER_H

#include <string>

#include "AbstractEntity.h"
#include "../IObservable.h"
#include "../IObserver.h"

class Character: public AbstractEntity, IObservable
{
protected:
    std::list<IObserver*> observers;
    std::string data;
    double X, Y, speed;
    int life;
    virtual void NotifyAll();
public:
    Character();
    virtual ~Character() = 0;
    virtual double GetX() const;
    virtual double GetY() const;
    virtual double GetSpeed() const;
    virtual int GetLife() const;
    virtual void SetX(double);
    virtual void SetY(double);
    virtual void SetSpeed(double);
    virtual void SetLife(int);
    virtual void AddObserver(IObserver*);
    virtual void RemoveObserver(IObserver*);
    virtual std::string& Serialize();
};


#endif //PLANTSVSZOMBIES_CHARACTER_H
