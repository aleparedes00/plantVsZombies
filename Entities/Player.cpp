//
// Created by Loïc Coquelet on 24/10/2018.
//

#include <iostream>

#include "Player.h"

bool Player::RemoveSuns(const int nb) {
    if (suns - nb < 0)
        return false;
    suns -= nb;
    return true;
}

void Player::CreateEntity() {

}

void Player::AddSuns(const int nb) {
    suns += nb;
}

Player::Player(Scene *scene) {
    this->scene = scene;
    this->suns = 0;
}

Player::~Player() {

}

void Player::HandleInput(Input *input) {
    std::cout << "Received input haha" << std::endl;
}
