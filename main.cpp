#include <SFML/Graphics.hpp>


//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(shape);
//        window.display();
//    }
//
//    return 0;
//}

#include <iostream>
#include "GameContext/GameLoop.h"
//#include <string>
//
//#include "GameContext/TimeManager.h"
//#include "Entities/AbstractEntity.h"
//#include "Entities/Character.h"
//#include "Entities/ZombieMonster.h"
//#include "MonsterFactory.h"
//#include "GameContext/Scene.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    GameLoop gameLoop = GameLoop();

    while (window.isOpen())
    {
        gameLoop.run(&window);
    }

//    MonsterFactory *fact = new MonsterFactory;
//    Scene *scene = new Scene;
//    Character *zombie = fact->Create("ZombieMonster");
//    zombie->SetX(3);
//    zombie->SetY(18);
//    zombie->SetLife(49);
//    scene->AddEntity(zombie);
//    Character *zombie2 = fact->Create("ZombieMonster");
//    zombie2->SetX(30);
//    zombie2->SetY(1);
//    zombie2->SetLife(7);
//    scene->AddEntity(zombie2);
//    string sceneSerial = scene->Serialize();
//    string serializedZombie = zombie->Serialize();
//    Scene *scene2 = new Scene(sceneSerial);
//    string sceneSerial2 = scene2->Serialize();
//    cout << "Scene egales ? : " << (sceneSerial == sceneSerial2) << endl;
    /*cout<< "Copy Life : " << copy->GetLife() << endl;
    cout<< "Copy X : " << copy->GetX() << endl;
    cout<<"Copy Y : " << copy->GetY() << endl;*/

    return 0;
}
