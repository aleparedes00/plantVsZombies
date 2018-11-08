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
    sf::Font *font;
    sf::Text *text;
    sf::Text *text2;
    sf::RenderWindow *window;
    bool running;
    Input* input;
    static TimeManager *manager;
    void EventToInput(sf::Event);
public:
    GameLoop(sf::RenderWindow&);

    ~GameLoop();

    void run();

    static unsigned int GetStartedTime();
};


#endif //PLANTSVSZOMBIES_GAMELOOP_H
