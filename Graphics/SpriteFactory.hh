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
#include "ImageModel.h"

class Character;

class SpriteFactory {
private:
    static sf::Sprite *SetZombieSprite(sf::Sprite*);
    static sf::Sprite *SetSunSprite(sf::Sprite*);
    static float CastDoubleToFloat(double x);
public:
    static ImageModel *CreateImage(std::string, float, float);
};


#endif //PLANTVSZOMBIES_MODELSPRITE_HH
