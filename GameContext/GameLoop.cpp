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
    if (event.type == sf::Event::EventType::KeyPressed){
        if (event.key.code == sf::Keyboard::Space){
            std::cout << "SPAAAAAAACEEEEEEEE !!!" << std::endl;
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            std::cout << "Left" << std::endl;
            ButtonClick();
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            std::cout << "Right" << std::endl;
            ButtonClick();
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)){
            std::cout << "Middle" << std::endl;
            ButtonClick();
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::XButton1)){
            std::cout << "X1" << std::endl;
            ButtonClick();
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::XButton2)){
            std::cout << "X2" << std::endl;
            ButtonClick();
        } else if (event.key.code == sf::Keyboard::Escape){
            std::cout << "Quitting !!!" << std::endl;
            this->running = false;
        }
    }
    this->input = new Input;
}

void GameLoop::ButtonClick(){
    sf::Vector2i position = sf::Mouse::getPosition();
    std::cout << "Mouse X : " << position.x << " || Mouse Y : " << position.y << std::endl;
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
        running = running && !scene->CheckDefeat(); // Checking defeat last to avoid doing another loop

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
