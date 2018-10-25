//
// Created by Loïc Coquelet on 23/10/2018.
//


#include "MonsterFactory.h"
#include "Entities/ZombieMonster.h"

#include "json.hpp"
using json = nlohmann::json;


Character* MonsterFactory::Create(const std::string& name)
{
    if(name == "ZombieMonster")
        return new ZombieMonster;
    else
        return nullptr;
}

Character* MonsterFactory::Unserialize(const std::string& data)
{
    json j = json::parse(data);
    Character *character;
    if ("ZombieMonster" == j["name"])
        character = new ZombieMonster;
    else
        return new ZombieMonster;
    character->SetLife(j["Life"].get<int>());
    character->SetX(j["X"].get<double>());
    character->SetY(j["Y"].get<double>());
    return character;
}

