#pragma once
#include "UI.h"
// #include "ECS.h"
#include "v2/ECS2.h"
#include <stdio.h>

#define Hub 0
#define Garden 1
#define Dungeon 2

#define ITEM_BUFFER_LEN 1236

unsigned char game_state = 0;
unsigned char game_location = 0;

itemBuffer items;
entityBuffer world;

entity background[50] = {};

void switch_location(int i, entity *e_buffer){
    if (i > Dungeon) game_location = Hub;
    else if (i < Hub) game_location = Dungeon;
    else game_location = i;

    switch(game_location){
        case Hub:
        // Load a preset Hub room
        break;
        
        case Garden:
        // Load the basic grid with the garden's plant data loaded
        break;

        case Dungeon:
        add_entity(entity_buffer, e_buffer + 1, (1048 - 50) / 2, (680 - 50) / 2); // TODO: check if bitshifting is viable
        // Generate a dungeon with rooms
        // Load the first room into the buffer (The doors will choose which part of the dungeon will be loaded next into the render buffer)
        break;
    }

    printf("World Size: %i and capacity: %i\n", world.size, world.cap);

    // Switch rendering to whichever buffer is needed
    // Set World = {insert preset buffer or Hub dungeon generation}
    // free the world and then init to the size you need
}
