//
// Created by Loïc Coquelet on 24/10/2018.
//

#include "GameLoop.h"
#include "Scene.h"
#include <iostream>

TimeManager *GameLoop::manager = &TimeManager::GetInstance();

GameLoop::GameLoop() {
    this->running = true;
}

GameLoop::~GameLoop() {}

void GameLoop::EventToInput(sf::Event event) {
    //TODO Convert event into input
    this->input = new Input;
}

void GameLoop::run(sf::RenderWindow *window) {
    Scene *scene = new Scene;
    sf::Event event;
    double lag = 0.0;
    unsigned int loops = 0;
    double step = 1;

    std::cout << "Starting manager" << std::endl;
    manager->Start();
    std::cout << "step : " << step << std::endl;
    while (running) {
        //std::cout << "New loop" << std::endl;
        manager->Update();

        lag += manager->GetElapsedTime();

        while (window->pollEvent(event)) {
            std::cout << "Getting event !" << std::endl;
            EventToInput(event);
        }

        if (event.type == sf::Event::Closed) {
            std::cout << "Window closed" << std::endl;
            window->close();
        }

        std::cout << "Window updated : " << (double)(lag * 1000) << " || Elapsed : " << (double)(manager->GetElapsedTime() * 1000) << std::endl;
        while (lag > step) {
            scene->Update(input);
            lag -= step;
            loops++;
        }
        std::cout << "End of loop : " << loops << std::endl;
        //std::cout << "Window updated : " << lag << " || Elapsed : " << manager->GetElapsedTime() << std::endl;

        //Graphic

        window->clear();
        //scene->Draw(lag / step);
        //std::cout << "Graphic leftover : " << (1000 * lag / step) << std::endl;
        window->display();
        running = !scene->CheckDefeat();
        //std::cout << "End of loop : " << loops << std::endl;
        std::cout << "Seconds since start : " << manager->GetStartedTime() / 1000 << std::endl;
        if (manager->GetStartedTime() > 0)
            std::cout << "Steps per second : " << loops / (double)(manager->GetStartedTime() / 1000) << std::endl;
    }
    std::cout << "Start : " << manager->GetStartedTime() / 1000 << std::endl;
    //TODO Cleanup logic ?
}

unsigned int GameLoop::GetStartedTime() {
    return manager->GetStartedTime();
}
