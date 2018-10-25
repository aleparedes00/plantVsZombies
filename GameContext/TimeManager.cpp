//
// Created by Loïc Coquelet on 23/10/2018.
//


#include "TimeManager.h"
#include <chrono>

TimeManager TimeManager::instance=TimeManager();

TimeManager::TimeManager()
{
}

TimeManager::~TimeManager()
{
}


TimeManager& TimeManager::GetInstance()
{
    return instance;
}

void TimeManager::Start()
{
    counter = 0;
    t2 = std::chrono::system_clock::now();
}

void TimeManager::Update()
{
    if (counter != 0)
        t2 = t1;
    t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = t1 - t2;
    counter += elapsed.count() * 1000;
}

unsigned int TimeManager::GetElapsedTime()
{
    if (counter != 0)
    {
        std::chrono::duration<double> elapsed = t1 - t2;
        return elapsed.count() * 1000;
    } else
        return 0;
}

unsigned int TimeManager::GetStartedTime() const
{
    return counter;
}


