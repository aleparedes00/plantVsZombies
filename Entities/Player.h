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
    static Scene *scene;
    static bool RemoveSuns(const int);
    Input *input;

    sf::Text* text;
    sf::Font* font;
    void SetPrintableSun();
public:
    Player(Scene*);
    ~Player();
    static Character *GetPlant(int x_pos, int y_pos);
    void HandleInput(Input *input);
    void Draw(double, sf::RenderWindow&);
    void SetInput(Input&);
    static void AddSuns();
    void ColorPrintableSun();
};


#endif //PLANTSVSZOMBIES_PLAYER_H
