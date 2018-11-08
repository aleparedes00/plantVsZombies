//
// Created by Alejandra Paredes on 01/11/2018.
//

#ifndef PLANTVSZOMBIES_MODELSPRITE_HH
#define PLANTVSZOMBIES_MODELSPRITE_HH


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Entities/Character.h"

class Character;

class SpriteFactory {
private:
    std::string type;
    sf::Texture texture;
    sf::Sprite sprite;

    void SetSprite(std::string file);
    float CastToFloat(double x);

public:
    SpriteFactory(std::string , float, float);
    ~SpriteFactory();
    void Draw(float, float, sf::RenderWindow&);
    void Draw(Character*, double, sf::RenderWindow&);
};


#endif //PLANTVSZOMBIES_MODELSPRITE_HH
