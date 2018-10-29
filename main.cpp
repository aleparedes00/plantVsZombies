#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameContext/GameLoop.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Starting the game !");
    GameLoop gameLoop = GameLoop(window);
    gameLoop.run();
    std::cout << "Exited gameloop" << std::endl;
    if (window.isOpen())
        window.close();
    std::cout << "Exiting application" << std::endl;
    return 0;
}
