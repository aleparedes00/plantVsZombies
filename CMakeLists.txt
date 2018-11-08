cmake_minimum_required(VERSION 3.2)
project(plantVsZombies)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(.)
include_directories(Entities)
include_directories(GameContext)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -pedantic")


add_executable(plantVsZombies
        Entities/AbstractEntity.cpp
        Entities/AbstractEntity.h
        Entities/Character.cpp
        Entities/Character.h
        Entities/Player.cpp
        Entities/Player.h
        Entities/ZombieMonster.cpp
        Entities/ZombieMonster.h
        GameContext/GameLoop.cpp
        GameContext/GameLoop.h
        GameContext/Input.cpp
        GameContext/Input.h
        GameContext/Lane.cpp
        GameContext/Lane.h
        GameContext/Scene.cpp
        GameContext/Scene.h
        GameContext/TimeManager.cpp
        GameContext/TimeManager.h
        IObservable.h
        Config.h
        IObserver.h
        ISerializable.h
        json.hpp
        main.cpp
        Entities/Plant.h
        Entities/Plant.cpp
        Entities/PlantProjectile.h
        Entities/PlantProjectile.cpp
        Entities/EntityFactory.h
        Entities/EntityFactory.cpp
        MonsterFactory.cpp
        MonsterFactory.h
        Graphics/SpriteFactory.cpp
        Graphics/SpriteFactory.hh
        )

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(plantVsZombies ${SFML_LIBRARIES})
endif ()