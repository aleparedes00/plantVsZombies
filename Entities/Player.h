//
// Created by Loïc Coquelet on 24/10/2018.
//

#ifndef PLANTSVSZOMBIES_PLAYER_H
#define PLANTSVSZOMBIES_PLAYER_H


#include "../GameContext/Scene.h"
#include <SFML/Graphics.hpp>

class Scene;

class Player {
private:
    static int suns;
    Scene *scene;
    bool RemoveSuns(const int);
    void CreateEntity();
    Input *input;
public:
    Player(Scene*);
    ~Player();
    void HandleInput(Input *input);
    void Draw(double, sf::RenderWindow&);
    void SetInput(Input&);
    static void AddSuns();
};


#endif //PLANTSVSZOMBIES_PLAYER_H
