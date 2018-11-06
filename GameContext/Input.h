//
// Created by Loïc Coquelet on 24/10/2018.
//

#ifndef PLANTSVSZOMBIES_INPUT_H
#define PLANTSVSZOMBIES_INPUT_H


#include <SFML/Window/Event.hpp>
enum class Types {
    ButtonDown, // Button is being kept pushed
    LeftButtonPressed,// Button just got pushed
    RightButtonPressed,// Button just got pushed
    ButtonReleased, // Button just stopped being pushed
    ButtonUp // Button has not been touched
};

class Input {
private:
    Types type;
    unsigned int X,Y;
public:
    Input(Types, unsigned int, unsigned int);
    ~Input();
    Types GetType();
    unsigned int GetX();
    unsigned int GetY();
};


#endif //PLANTSVSZOMBIES_INPUT_H
