//
// Created by Loïc Coquelet on 08/11/2018.
//

#ifndef PLANTVSZOMBIES_IMAGE_H
#define PLANTVSZOMBIES_IMAGE_H

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Entities/Character.h"

class ImageModel {
private:
    sf::Texture *texture;
    sf::Sprite *sprite;

public:
    ImageModel(sf::Sprite*, sf::Texture*);

    ~ImageModel();

    void Draw(float, float, sf::RenderWindow &);

    void Draw(Character *, double, sf::RenderWindow &);

    sf::Sprite GetSprite();
};


#endif //PLANTVSZOMBIES_IMAGE_H
