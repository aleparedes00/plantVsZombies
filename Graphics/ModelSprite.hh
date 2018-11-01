//
// Created by Alejandra Paredes on 01/11/2018.
//

#ifndef PLANTVSZOMBIES_MODELSPRITE_HH
#define PLANTVSZOMBIES_MODELSPRITE_HH


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "ISprite.hh"

class ModelSprite: public ISprite {
private:
    sf::Texture texture;
    sf::Sprite sprite;

public:
    ModelSprite(std::string data, float positionX, float positionY);
    ~ModelSprite();
    void SetPosition(float X, float Y);
    void Draw(double, sf::RenderWindow&);
    void GetTextureInformation();
};


#endif //PLANTVSZOMBIES_MODELSPRITE_HH
