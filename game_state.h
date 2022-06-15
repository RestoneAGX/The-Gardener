#include <stdlib.h>

#define In_Game 0
#define UI 1

#define Start 0
#define Hub 1
#define Dungeon 2

#define Armor_Slots 4
#define Inventory_Slots 32 //Actually 16 but 2 uint8 per slot

enum armor_types {Accessory, Chest, Legs, Shoes};
 
unsigned char game_state = 0;
unsigned char game_location = 0;

unsigned char *armor;
unsigned char *inventory;

void switch_location(int i, void (*free_world)(void *), void * world){
    if (game_location == Dungeon) free_world(world);
    
    if (i > Dungeon) game_location = Start;
    else if (i < Start) game_location = Dungeon;
    else game_location = i;

    // Switch rendering to whichever buffer is needed
    // Set World = {insert preset buffer or start dungeon generation}
    // free the world and then init to the size you need
}

void init_storage(){
    armor = (unsigned char *) malloc (Armor_Slots);
    inventory = (unsigned char *) malloc(Inventory_Slots);
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