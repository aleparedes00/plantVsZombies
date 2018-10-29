//
// Created by Loïc Coquelet on 24/10/2018.
//

#ifndef PLANTSVSZOMBIES_PLAYER_H
#define PLANTSVSZOMBIES_PLAYER_H


#include "../GameContext/Scene.h"

class Scene;

class Player {
private:
    int suns;
    Scene *scene;
    bool RemoveSuns(const int);
    void CreateEntity();
    void AddSuns(const int);

public:
    Player(Scene*);
    ~Player();
    void HandleInput(Input *input);
};


#endif //PLANTSVSZOMBIES_PLAYER_H
