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
    unsigned int loops = 0; // Number of loops for GAMEPLAY only, not including graphics
    double step = 33; // DO NOT MODIFY, THIS IS THE SPEED OF THE GAME, or called time step
    double leftover = 0; // Time left between two gameplay updates

    std::cout << "Starting manager" << std::endl;
    manager->Start();

    while (running) {
        manager->Update();

        lag += manager->GetElapsedTime(); // Lag is the time between two frames

        while (window->pollEvent(event)) {
            //std::cout << "Getting event !" << std::endl;
            EventToInput(event);
        }

        if (event.type == sf::Event::Closed) {
            std::cout << "Window closed" << std::endl;
            window->close();
        }

        while (lag >= step) { // GAMEPLAY LOOP. Physics happen here at fixed time steps. This means no one calls GetElapsedTime from the Time Manager.
            scene->Update(input);
            lag -= step;
            loops++;
        }
        leftover = lag / step; // Time left between two frames
        //std::cout << "Graphic leftover : " << leftover << std::endl;

        //Graphic

        window->clear();
        //scene->Draw(leftover); // Graphics are drawn using an interpolation between current and next step
        window->display();
        running = !scene->CheckDefeat(); // Checking defeat last to avoid doing another loop

        //std::cout << "Seconds since start : " << manager->GetStartedTime() / 1000.0 << std::endl;
//        if (manager->GetStartedTime() > 0)
//            std::cout << "Steps per second : " << loops / (manager->GetStartedTime() / 1000.0) << std::endl;
//        std::cout << "Total steps : " << loops << std::endl;

    }
    std::cout << "End of the game !" << std::endl;
    std::cout << "Seconds since Start : " << manager->GetStartedTime() / 1000 << std::endl;
    //TODO Cleanup logic ?
}

unsigned int GameLoop::GetStartedTime() {
    return manager->GetStartedTime();
}
