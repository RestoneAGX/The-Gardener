#include <stdlib.h>

#define Armor_Slots 4
#define Inventory_Slots 32 //Actually 16 but 2 uint8 per slot

enum armor_types {Accessory, Chest, Legs, Shoes};

unsigned char *armor;
unsigned char *inventory;

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
    // if (new_slot >= max || new_slot % 2 == 1) return; // No need to add this check since the behaviour itself would be wrong to begin with
    
    storage[new_slot++] = storage[old_slot++];
    storage[new_slot] = storage[old_slot];
}

void remove_item(unsigned char *storage, size_t max, int slot){
    // if (slot >= max || slot % 2 == 1) return;
    storage[slot] = 0;
}


//Save and Load functions here