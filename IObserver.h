//
// Created by Loïc Coquelet on 23/10/2018.
//

#ifndef PLANTSVSZOMBIES_IOBSERVER_H
#define PLANTSVSZOMBIES_IOBSERVER_H


#include "IObservable.h"

class IObservable;

class IObserver{
public:
    virtual ~IObserver(){}
    virtual void Notify(IObservable*) = 0;
};

#endif //PLANTSVSZOMBIES_IOBSERVER_H
