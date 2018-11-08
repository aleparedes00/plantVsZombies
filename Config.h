//
// Created by Loïc Coquelet on 01/11/2018.
//

#ifndef PLANTSVSZOMBIES_CONFIG_H
#define PLANTSVSZOMBIES_CONFIG_H

// Graphic configuration

#define X_RESOLUTION 1024
#define Y_RESOLUTION 768

#define Y_OFFSET_BEFORE_LANE Y_RESOLUTION / 5
#define LANE_WIDTH 450
#define LANE_HEIGHT 50

// Gameplay configuration

#define LANE_NUMBER 5
#define CELL_NUMBER 9
#define WAVE_DURATION 30



#define CELL_SIZE 50
#define CELL_INTERVAL 40
#define CELL_SPACING (CELL_SIZE + CELL_INTERVAL)
#define Y_OFFSET 200
#define X_OFFSET 20

// Graphics files
#define ZOMBIE_SPRITE "../Graphics/Resources/Images/zombie2.png"
#define SUN_SPRITE "../Graphics/Resources/Images/sun.png"

#endif //PLANTSVSZOMBIES_CONFIG_H
