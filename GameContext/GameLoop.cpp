//
// Created by Loïc Coquelet on 24/10/2018.
//

#include "GameLoop.h"
#include "Scene.h"
#include <iostream>
#include <string>

TimeManager *GameLoop::manager = &TimeManager::GetInstance();

GameLoop::GameLoop(sf::RenderWindow &window) {
    std::cout << "Start of the gameloop initialization" << std::endl;
    this->running = true;
    this->window = &window;
    this->input = new Input(Types::ButtonUp, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

    this->text = new sf::Text();
    this->font = new sf::Font();
    if (font->loadFromFile(FONT_FILE)) {
        std::cout << "Found font" << std::endl;
    } else {
        std::cout << "Problem setting font" << std::endl;
    }
    this->text->setFont(*font);
    this->text->setString("Start");
    text->setStyle(sf::Text::Bold);
    text->setPosition(350, 20);
    std::cout << "End of the gameloop initialization" << std::endl;
}

GameLoop::~GameLoop() {}

void GameLoop::EventToInput(sf::Event event) {
    //TODO Convert event into input
    this->input = new Input(Types::ButtonUp, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
    if (event.type == sf::Event::EventType::KeyPressed){
        if (event.key.code == sf::Keyboard::Space){
            std::cout << "SPAAAAAAACEEEEEEEE !!!" << std::endl;
        } else if (event.key.code == sf::Keyboard::Escape){
            std::cout << "Quitting !!!" << std::endl;
            this->running = false;
        }
    } else if (event.type == sf::Event::EventType::MouseButtonPressed) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            std::cout << "Left : " << sf::Mouse::getPosition(*window).x << " | " << sf::Mouse::getPosition(*window).y << std::endl;
            this->input = new Input(Types::LeftButtonPressed, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            this->input = new Input(Types::RightButtonPressed, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
            std::cout << "Right : " << sf::Mouse::getPosition(*window).x << " | " << sf::Mouse::getPosition(*window).y << std::endl;
        }
    }
}

void GameLoop::run() {
    Scene *scene = new Scene;
    sf::Event event;
    double lag = 0.0;
    unsigned int loops = 0; // Number of loops for GAMEPLAY only, not including graphics
    unsigned int totalLooops = 0; // Total of graphic loops
    const double step = 33; // DO NOT MODIFY, THIS IS THE SPEED OF THE GAME, or called time step
    double leftover = 0; // Time left between two gameplay updates
    double deltaTime;
    int secondsSinceStart = 0;
    int fps = 0;


    std::cout << "Starting manager" << std::endl;
    manager->Start();
    while (running) {
        manager->Update();

        deltaTime = manager->GetElapsedTime();
        lag += deltaTime; // Lag is the time between two frames

        while (window->pollEvent(event)) {
            EventToInput(event);
            if (event.type == sf::Event::Closed) {
                std::cout << "Window closed" << std::endl;
                running = false;
                window->close();
            }
        }
        //std::cout << "End of pollEvent" << std::endl;

        while (lag >= step) { // UPDATE LOOP. Physics happen here at fixed time steps. This means no one calls GetElapsedTime from the Time Manager.
            scene->Update(*input);
            lag -= step;
            loops++;
        }
        //std::cout << "End of Update loop" << std::endl;
        leftover = lag / step; // Time left between two frames
        //std::cout << "Graphic leftover : " << leftover << std::endl;

        //Graphic

        window->clear();


        if (secondsSinceStart < (GameLoop::GetStartedTime() / 1000.0)) {
            fps = 1000 / deltaTime;
            secondsSinceStart++;
            std::string toast = "Time : " + std::to_string(secondsSinceStart) +  "                         FPS : " + std::to_string(fps);
            text->setString(toast);
        }
//        std::cout << "Before text !" << std::endl;
        window->draw(*text);
//        std::cout << "After text !" << std::endl;
        scene->Draw(leftover, *(window)); // Graphics are drawn using an interpolation between current and next step
        //std::cout << "End of Draw loop" << std::endl;
        window->display();
        //std::cout << "Displaying" << std::endl;
        running = running && !scene->CheckDefeat(); // Checking defeat last to avoid doing another loop

//        std::cout << "Seconds since start : " << manager->GetStartedTime() / 1000.0 << std::endl;
//        if (manager->GetStartedTime() > 0)
//            std::cout << "Steps per second : " << loops / (manager->GetStartedTime() / 1000.0) << std::endl;
//        std::cout << "Total steps : " << loops << std::endl;

        totalLooops++;
    }
    std::cout << "End of the game !" << std::endl;
    std::cout << "Seconds since Start : " << manager->GetStartedTime() / 1000 << std::endl;
    std::cout << "Steps per second since start : " << loops / (manager->GetStartedTime() / 1000) << std::endl;
    std::cout << "Frames per second since start : " << totalLooops / (manager->GetStartedTime() / 1000) << std::endl;
    //TODO Cleanup logic ?
}

unsigned int GameLoop::GetStartedTime() {
    return manager->GetStartedTime();
}
