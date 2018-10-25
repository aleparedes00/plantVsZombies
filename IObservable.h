//
// Created by Loïc Coquelet on 23/10/2018.
//

#ifndef PLANTSVSZOMBIES_IOBSERVABLE_H
#define PLANTSVSZOMBIES_IOBSERVABLE_H

#include <list>
#include "IObserver.h"

class IObserver;

class IObservable{
protected:
    std::list<IObserver*> observers;
public:
    virtual ~IObservable() {}
    virtual void AddObserver(IObserver*) = 0;
    virtual void RemoveObserver(IObserver*) = 0;
};

#endif //PLANTSVSZOMBIES_IOBSERVABLE_H
