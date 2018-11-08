//
// Created by Loïc Coquelet on 24/10/2018.
//

#include <iostream>

#include "Player.h"
#include "EntityFactory.h"
#define SUN_ADD 10
#define PLANT_PRICE 30

int Player::suns = 0;
Scene *Player::scene;

bool Player::RemoveSuns(const int nb) {
    if (suns - nb < 0)
        return false;
    suns -= nb;
    return true;
}

Character *Player::GetPlant(int x_pos, int y_pos) {
    Character *plant = nullptr;
    if (RemoveSuns(PLANT_PRICE)) {
        plant = EntityFactory::Create("Plant");
        plant->SetX(x_pos);
        std::cout << "Suns after plant creation : " << suns << std::endl;
    } else
        std::cout << "Not enough suns for new plant : " << suns << std::endl;
    return plant;
}

void Player::AddSuns() {

    suns += SUN_ADD;
    std::cout << "Suns after sun pickup : " << suns << std::endl;

}

Player::Player(Scene *scene) {
    Player::scene = scene;
    this->input = nullptr;
    this->SetPrintableSun();
}

Player::~Player() {

}

void Player::SetPrintableSun(){
    this->text = new sf::Text();
    this->font = new sf::Font();
    if (font->loadFromFile(FONT_FILE)){
        std::cout << "Found font" << std::endl;
    } else {
        std::cout << "Problem setting font" << std::endl;
    }
    this->text->setFont(*font);
    this->text->setString("Suns");
    text->setStyle(sf::Text::Bold);

    text->setPosition(20, 20);
}

void Player::ColorPrintableSun() {
    if(this->suns >= 30){
        this->text->setFillColor(sf::Color::Yellow);
    } else{
        this->text->setFillColor(sf::Color::Red);
    }
}
void Player::Draw(double leftover, sf::RenderWindow &window){
    text->setString(std::to_string(suns));
    ColorPrintableSun();
    window.draw(*text);
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
