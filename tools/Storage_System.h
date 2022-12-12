#pragma once
#include <stdio.h>
#include <stdlib.h>

#define Armor_Slots 4
#define Inventory_Slots 32 //Actually 16 but 2 uint8 per slot

enum armor_types {Accessory, Chest, Legs, Shoes};

unsigned char armor[Armor_Slots];
unsigned char inventory[Inventory_Slots];

void add_item(unsigned char *storage, size_t max, unsigned char id, unsigned char amount){
    for (int i = 0; i < max; i += 2)
        if (!storage[i]){
            storage[i] = id;
            storage[i+1] = amount;
        }
}

void move_item(unsigned char *storage, size_t max, int old_slot, int new_slot){
    storage[new_slot++] = storage[old_slot++];
    storage[new_slot] = storage[old_slot];
}

void remove_item(unsigned char *storage, int slot){
    storage[slot] = 0;
}


void Save_Game(){
    FILE* fd = fopen("Game.save", "w+");

    fwrite(armor, 1, Armor_Slots, fd);
    fwrite(inventory, 1, Inventory_Slots, fd);

    fclose(fd);
}

void Load_Game(){
    FILE* fd = fopen("Game.save", "r");

    for (int i = 0; i < Armor_Slots;  i++)
        armor[i] = (unsigned char) fgetc(fd);

    for (int i = 0; i < Inventory_Slots; i++)
        inventory[i] = (unsigned char) fgetc(fd);

    fclose(fd);
}
