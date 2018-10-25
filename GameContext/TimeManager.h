//
// Created by Loïc Coquelet on 23/10/2018.
//

#ifndef PLANTSVSZOMBIES_TIMEMANAGER_H
#define PLANTSVSZOMBIES_TIMEMANAGER_H

#include <chrono>

class TimeManager
{
private:
    unsigned int counter;
    std::chrono::system_clock::time_point t1, t2;

    TimeManager& operator= (const TimeManager&);
    TimeManager (const TimeManager&);

    static TimeManager instance;
    TimeManager();
    ~TimeManager();
public:
    static TimeManager& GetInstance();

    void Start();
    void Update();
    unsigned int GetElapsedTime();
    unsigned int GetStartedTime() const;
};


#endif //PLANTSVSZOMBIES_TIMEMANAGER_H
