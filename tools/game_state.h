#pragma once
#include "ECS.h"

#define Hub 0
#define Garden 1
#define Dungeon 2
 
unsigned char game_state = 0;
unsigned char game_location = 0;

entity background[50] = {};
world_array world;

void switch_location(int i, entity *e_buffer){
    if (i > Dungeon) game_location = Hub;
    else if (i < Hub) game_location = Dungeon;
    else game_location = i;

    free_world(&world);

    switch(game_location){
        case Hub:
        init_world(&world, 25);
        // Load a preset Hub room
        break;
        
        case Garden:
        init_world(&world, 50);
        // Load the basic grid with the garden's plant data loaded
        break;

        case Dungeon:
        init_world(&world, 50);
        add_element(&world, e_buffer + 1, (1048 - 50) / 2, (680 - 50) / 2); // TODO: Do error handling later.
        // Buffer itself has a finite size
        // Generate a dungeon with rooms
        // Load the first room into the buffer (The doors will choose which part of the dungeon will be loaded next into the render buffer)
        break;
    }

    printf("World Size: %i and capacity: %i\n", world.size, world.cap);

    // Switch rendering to whichever buffer is needed
    // Set World = {insert preset buffer or Hub dungeon generation}
    // free the world and then init to the size you need
}
