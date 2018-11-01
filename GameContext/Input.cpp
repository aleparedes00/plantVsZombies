//
// Created by Loïc Coquelet on 24/10/2018.
//

#include "Input.h"

Input::Input(Types type, const unsigned int X, const unsigned int Y) {
    this->type = type;
    this->X = X;
    this->Y = Y;
}

Input::~Input() {

}

Types Input::GetType() {
    return this->type;
}

unsigned int Input::GetX() {
    return this->X;
}

unsigned int Input::GetY() {
    return this->Y;
}
