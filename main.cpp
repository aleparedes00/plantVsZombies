#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameContext/GameLoop.h"
#include "Config.h"

int main()
{
    std::cout << "Start of the game" << std::endl;
    sf::RenderWindow window(sf::VideoMode(X_RESOLUTION, Y_RESOLUTION), "Starting the game !");
    GameLoop gameLoop = GameLoop(window);
    std::cout << "Start of the gameloop" << std::endl;
    gameLoop.run();
    std::cout << "Exited gameloop" << std::endl;
    if (window.isOpen())
        window.close();
    std::cout << "Exiting application" << std::endl;
    return 0;
}
