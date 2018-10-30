//
// Created by Loïc Coquelet on 24/10/2018.
//

#include "GameLoop.h"
#include "Scene.h"
#include <iostream>
#include <string>

TimeManager *GameLoop::manager = &TimeManager::GetInstance();

GameLoop::GameLoop(sf::RenderWindow &window) {
    this->running = true;
    this->window = &window;
}

GameLoop::~GameLoop() {}

void GameLoop::EventToInput(sf::Event event) {
    //TODO Convert event into input
    if (event.type == sf::Event::EventType::KeyPressed){
        if (event.key.code == sf::Keyboard::Space){
            std::cout << "SPAAAAAAACEEEEEEEE !!!" << std::endl;
        } else if (event.key.code == sf::Keyboard::Escape){
            std::cout << "Quitting !!!" << std::endl;
            this->running = false;
        }
    } else if (event.type == sf::Event::EventType::MouseButtonPressed) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            std::cout << "Left" << std::endl;
            this->input = new Input(Types::ButtonPressed, sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
        } /*else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            std::cout << "Right" << std::endl;
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)){
            std::cout << "Middle" << std::endl;
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::XButton1)){
            std::cout << "X1" << std::endl;
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::XButton2)){
            std::cout << "X2" << std::endl;
        } */
    } else if (event.type == sf::Event::EventType::TouchBegan) {
        std::cout << "Touch began" << std::endl;
    } else if (event.type == sf::Event::EventType::TouchEnded) {
        std::cout << "Touch ended" << std::endl;
    } else if (event.type == sf::Event::EventType::TouchMoved) {
        std::cout << "Touch moved" << std::endl;
    }
    this->input = new Input(Types::ButtonUp, sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
}

//void GameLoop::ButtonClick(){
//    sf::Vector2i position = sf::Mouse::getPosition(*(window));
//    std::cout << "Mouse X : " << position.x << " || Mouse Y : " << position.y << std::endl;
//}

void GameLoop::run() {
    Scene *scene = new Scene;
    sf::Event event;
    double lag = 0.0;
    unsigned int loops = 0; // Number of loops for GAMEPLAY only, not including graphics
    const double step = 33; // DO NOT MODIFY, THIS IS THE SPEED OF THE GAME, or called time step
    double leftover = 0; // Time left between two gameplay updates
    double deltaTime;

//    sf::Font font;
//    font.loadFromFile("impact.ttf");
//    sf::Text text("hello", font);
//    text.setCharacterSize(24);
//    text.setFont(font);
//    text.setPosition(400, 20);

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

        while (lag >= step) { // GAMEPLAY LOOP. Physics happen here at fixed time steps. This means no one calls GetElapsedTime from the Time Manager.
            scene->Update(*(input));
            lag -= step;
            loops++;
        }
        leftover = lag / step; // Time left between two frames
        //std::cout << "Graphic leftover : " << leftover << std::endl;

        //Graphic

        window->clear();


//        if (deltaTime > 0) {
//            double fps = 1000.0 / deltaTime;
//            std::string toast = "FPS : " + std::to_string(fps);
//            text.setString(toast);
//            window->draw(text);
//        }
        scene->Draw(leftover, *(window)); // Graphics are drawn using an interpolation between current and next step
        window->display();
        running = running && !scene->CheckDefeat(); // Checking defeat last to avoid doing another loop

        //std::cout << "Seconds since start : " << manager->GetStartedTime() / 1000.0 << std::endl;
//        if (manager->GetStartedTime() > 0)
//            std::cout << "Steps per second : " << loops / (manager->GetStartedTime() / 1000.0) << std::endl;
//        std::cout << "Total steps : " << loops << std::endl;
    }
    std::cout << "End of the game !" << std::endl;
    std::cout << "Seconds since Start : " << manager->GetStartedTime() / 1000 << std::endl;
    std::cout << "Debug" << std::endl;
    //TODO Cleanup logic ?
}

unsigned int GameLoop::GetStartedTime() {
    return manager->GetStartedTime();
}
