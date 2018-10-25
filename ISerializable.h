//
// Created by Loïc Coquelet on 23/10/2018.
//

#ifndef PLANTSVSZOMBIES_ISERIALIZABLE_H
#define PLANTSVSZOMBIES_ISERIALIZABLE_H

#include <string>

class ISerializable{
public:
    virtual ~ISerializable() {}
    virtual std::string& Serialize() = 0;
};


#endif //PLANTSVSZOMBIES_ISERIALIZABLE_H
