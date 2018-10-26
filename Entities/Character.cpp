//
// Created by Loïc Coquelet on 23/10/2018.
//


#include "Character.h"
#include "../IObserver.h"
#include <iostream>
using namespace std;

Character::Character()
{
    this->observers = list<IObserver*>();
    this->data = "abstract";
}

Character::~Character()
{
}

void Character::NotifyAll()
{
    list<IObserver*>::iterator it;
    for (it = this->observers.begin(); it != this->observers.end(); it++)
        (*it)->Notify(this);
    std::cout << "After Character notify all" << std::endl;
}

double Character::GetX() const
{
    return this->X;
}
double Character::GetY() const
{
    return this->Y;
}
int Character::GetLife() const
{
    return this->life;
}
void Character::SetX(double new_x)
{
    this->X = new_x;
    //std::cout << "After Character set x" << std::endl;
}
void Character::SetY(double new_y)
{
    this->Y = new_y;
}
void Character::SetLife(int new_life)
{
    this->life = new_life;
}

void Character::AddObserver(IObserver* observer)
{
    this->observers.push_back(observer);
}
void Character::RemoveObserver(IObserver* observer)
{
    this->observers.remove(observer);
}

std::string& Character::Serialize()
{
    return data;
}

