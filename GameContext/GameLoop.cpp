//
// Created by Loïc Coquelet on 24/10/2018.
//

#include "GameLoop.h"
#include "Scene.h"
#include <iostream>

#define MS_PER_UPDATE 60 / 1000

TimeManager *GameLoop::manager = &TimeManager::GetInstance();

GameLoop::GameLoop() {
    this->running = true;
}

GameLoop::~GameLoop() {}

void GameLoop::EventToInput(sf::Event event) {
    //TODO Convert event into input
    this->input = new Input;
}

void GameLoop::run(sf::RenderWindow* window) {
    Scene *scene = new Scene;
    sf::Event event;
    unsigned int lag = 0;

    std::cout << "Starting manager" << std::endl;
    manager->Start();
    while (running) {
        //std::cout << "New loop" << std::endl;
        manager->Update();

        lag += manager->GetElapsedTime();

        while (window->pollEvent(event)){
            std::cout << "Getting event !" << std::endl;
            EventToInput(event);
        }

        if (event.type == sf::Event::Closed)
            std::cout << "Window closed" << std::endl;
                window->close();

        while (lag  >= MS_PER_UPDATE){
            std::cout << "Window updated : " << lag  << " || Elapsed : " << manager->GetElapsedTime() << std::endl;
            scene->Update(input);
            lag -= MS_PER_UPDATE;
        }

        //Graphic

        window->clear();
        scene->Draw(lag / MS_PER_UPDATE);
        //std::cout << "Graphic leftover : " << (1000 * lag / MS_PER_UPDATE) << std::endl;
        window->display();
        if (scene->CheckDefeat())
            running = false;
        //std::cout << "End of loop" << std::endl;
    }
    //TODO Cleanup logic ?
}

unsigned int GameLoop::GetElapsedTime() {
    return manager->GetElapsedTime();
}
