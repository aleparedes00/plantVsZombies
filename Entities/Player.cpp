//
// Created by Loïc Coquelet on 24/10/2018.
//

#include <iostream>

#include "Player.h"

#define SUN_ADD 10

int Player::suns = 0;

bool Player::RemoveSuns(const int nb) {
    if (suns - nb < 0)
        return false;
    suns -= nb;
    return true;
}

void Player::CreateEntity() {

}

void Player::AddSuns() {
    suns += SUN_ADD;
    std::cout << "Suns : " << suns << std::endl;
}

Player::Player(Scene *scene) {
    this->scene = scene;
    this->input = nullptr;
}

Player::~Player() {

}

void Player::Draw(double leftover, sf::RenderWindow &window){
//    if (this->input != nullptr){
//        std::cout << "Drawing for player" << std::endl;
//        sf::Font font = sf::Font();
//        std::cout << "Got a font" << std::endl;
//        font.loadFromFile("impact.ttf");
//        std::cout << "Loaded it from file" << std::endl;
//        std::string str = "X : " + std::to_string(input->GetX()) + " || Y : " + std::to_string(input->GetY());
//        std::cout << "Woops converting : " << str << std::endl;
//        sf::Text text = sf::Text(sf::String(str), font);
//        std::cout << "That's a text object" << std::endl;
//        text.setCharacterSize(24);
//        std::cout << "With a character size" << std::endl;
//        text.setFont(font);
//        std::cout << "And a font" << std::endl;
//        text.setPosition(200, 200);
//        std::cout << "Now draw pls" << std::endl;
//        window.draw(text);
//        std::cout << "Fenetre" << std::endl;
//
//        std::cout << "Font : " << font.getInfo().family << std::endl;
//    }
}

void Player::SetInput(Input &input){
    this->input = &input;
}

void Player::HandleInput(Input *input) {
    std::cout << "Received input haha" << std::endl;
}
