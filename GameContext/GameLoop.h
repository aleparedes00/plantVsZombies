//
// Created by Loïc Coquelet on 24/10/2018.
//

#ifndef PLANTSVSZOMBIES_GAMELOOP_H
#define PLANTSVSZOMBIES_GAMELOOP_H

#include <list>
#include "Input.h"
#include "TimeManager.h"
#include "../IObserver.h"
#include <SFML/Graphics.hpp>

class GameLoop {
private:
    bool running;
    Input* input;
    static TimeManager *manager;
    void EventToInput(sf::Event);
public:
    GameLoop();

    ~GameLoop();

    void run(sf::RenderWindow*);

    static unsigned int GetStartedTime();
};


#endif //PLANTSVSZOMBIES_GAMELOOP_H
