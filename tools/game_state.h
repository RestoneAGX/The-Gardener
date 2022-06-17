#include <stdlib.h>

#define In_Game 0
#define UI 1

#define Hub 0
#define Garden 1
#define Dungeon 2

#define Normal 0 //TODO: Remove after publishing the game
#define Debug 1 //TODO: Remove after making the game

#define Armor_Slots 4
#define Inventory_Slots 32 //Actually 16 but 2 uint8 per slot

enum armor_types {Accessory, Chest, Legs, Shoes};
 
unsigned char game_state = 0;
unsigned char game_location = 0;

unsigned char *armor;
unsigned char *inventory;

unsigned char DebugMode = 0;

void switch_location(int i, void (*free_world)(void *), void (*init_world)(void *, size_t), void * world){
    if (game_location == Dungeon) free_world(world);
    
    if (i > Dungeon) game_location = Hub;
    else if (i < Hub) game_location = Dungeon;
    else game_location = i;

    free_world(world);

    switch(game_location){
        case Hub:
        init_world(world, 50);
        // Load a preset Hub room
        break;
        
        case Garden:
        init_world(world, 50);
        // Load the basic grid with the garden's plant data loaded
        break;

        case Dungeon:
        init_world(world, 50);
        // Buffer itself has a finite size
        // Generate a dungeon with rooms
        // Load the first room into the buffer (The doors will choose which part of the dungeon will be loaded next into the render buffer)
        break;
    }

    // Switch rendering to whichever buffer is needed
    // Set World = {insert preset buffer or Hub dungeon generation}
    // free the world and then init to the size you need
}

void init_storage(){
    armor = (unsigned char *) calloc(Armor_Slots, 1);
    inventory = (unsigned char *) calloc(Inventory_Slots, 1);
}

void add_item(unsigned char *storage, size_t max, unsigned char id, unsigned char amount){
    for (int i = 0; i < max; i += 2)
        if (!storage[i]){
            storage[i] = id;
            storage[i+1] = amount;
        }
}

void move_item(unsigned char *storage, size_t max, int old_slot, int new_slot){
    if (new_slot >= max || new_slot % 2 == 1) return;
    
    storage[new_slot] = storage[old_slot];
    storage[new_slot+1] = storage[old_slot+1];
}

void remove_item(unsigned char *storage, size_t max, int slot){
    if (slot >= max || slot % 2 == 1) return;
    storage[slot] = 0;
}


//Save and Load functions here