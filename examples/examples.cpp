#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include "TimeManager.hh"
#include "ZombieMonster.hh"

/*Detecter des coalisions https://www.sfml-dev.org/tutorials/2.0/graphics-transform-fr.php#bocutes-englobantes*/
/*detecter des coalisions*/
bool intersects(const sf::CircleShape &c1, const sf::CircleShape &c2) {
    sf::FloatRect circ1 = c1.getGlobalBounds();
    sf::FloatRect circ2 = c2.getGlobalBounds();

    return circ1.intersects(circ2);
}
/*recover the keyboards touchs*/
int gameTwoPlayer() {
    sf::VideoMode videomode(400, 400);
    sf::RenderWindow window(videomode, "GAME");
    sf::CircleShape circle;
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(100, 100);
    circle.setRadius(20);
    sf::CircleShape circle2;
    circle2.setFillColor(sf::Color::Yellow);
    circle2.setPosition(200, 200);
    circle2.setRadius(20);
    sf::CircleShape circle3;
    circle3.setFillColor(sf::Color::Black);
    circle3.setPosition(300, 300);
    circle3.setRadius(50);


    while (window.isOpen() && (!intersects(circle, circle3)) && (!intersects(circle2, circle3))) {
        window.clear(sf::Color::Blue);
        window.draw(circle);
        window.draw(circle2);
        window.draw(circle3);

        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up)) {
            circle.move(0, -0.5);


        } else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down)) {
            circle.move(0, 0.5);


        } else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right)) {
            circle.move(0.5, 0);


        } else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left)) {
            circle.move(-0.5, 0);


        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            circle2.move(0, -0.5);


        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            circle2.move(0, 0.5);


        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            circle2.move(0.5, 0);


        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            circle2.move(-0.5, 0);


        }


        if (intersects(circle, circle2)) {
            circle2.move(0.5, 0);
        }
        if (intersects(circle2, circle)) {
            circle.move(0.5, 0);

        }
        if (intersects(circle, circle3)) {

            std::cout << "Red loses";
        }
        if (intersects(circle2, circle3)) {

            std::cout << "Yellow loses";
        }
    }
    return 0;
}

void moveACircle() {

    sf::RenderWindow window(sf::VideoMode(900, 900, 32), "PlantsVsZombies");
    TimeManager &timeManager = TimeManager::GetInstance();

    // Circle
    sf::CircleShape circle;
    circle.setRadius(150);
    circle.setOutlineColor(sf::Color::Red);
    circle.setOutlineThickness(5);
    circle.setPosition(200, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            timeManager.Start();
            timeManager.Update();
            auto time = timeManager.GetElapsedTime();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            circle.move(200 + time, 0);
            window.clear(sf::Color::Black);
            window.draw(circle);
            window.display();
        }
    }
}

int main() {
    TimeManager &timeManager = TimeManager::GetInstance();
    sf::RenderWindow window(sf::VideoMode(900, 900, 32), "PlantsVsZombies");

    timeManager.Start();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            timeManager.Update();
            auto time = timeManager.GetElapsedTime()/1000;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout << time << std::endl;

            zombie.move(time*10, time*10);
            window.clear(sf::Color::Black);
            window.draw(zombie);
            window.display();
        }
    }
    return 0;
}