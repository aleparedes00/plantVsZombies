//
// Created by Loïc Coquelet on 23/10/2018.
//

#ifndef PLANTSVSZOMBIES_IOBSERVER_H
#define PLANTSVSZOMBIES_IOBSERVER_H

#include "Entities/AbstractEntity.h"

class IObservable;
class Character;

class IObserver{
public:
    virtual ~IObserver(){}
    virtual void Notify(IObservable*) = 0;
    virtual void Notify(AbstractEntity*) = 0;
    virtual void Notify(Character*) = 0;
};

#endif //PLANTSVSZOMBIES_IOBSERVER_H
