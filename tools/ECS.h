#pragma once
#include<stdlib.h>
#include<SDL2/SDL.h>

#define BitCheck(v,n) (v & (1 << n))
#define BitToggle(v,n) (v ^ (1 << n))
#define BitClear(v,n) (v & ~(1 << n))
#define BitSet(v,n) (v | (1 << n))

#define __OUT_OF_BOUNDS -2;

#define Renderable 0x1
#define Item 0x2

typedef struct entity{
    unsigned int indicator : 4;
    unsigned int id;
    unsigned char *components;
    SDL_FRect * sprite;
} entity;

int init_entity(entity *e, float x, float y){
    // e->sprite = atlas_buffer[e->id].sprite;
    e->sprite->x = x;
    e->sprite->y = y;

    switch(e->id){
        case 1: e->components = (unsigned char*) calloc(4, 1); // HP, Atk, Def, Speed //Also Place default stats
        e->components[0] = 255;
        break;
        case 0: e->components = (unsigned char*) calloc(10, 1); //Allocate memory according to ID
        e->components[0] = 255;
        e->components[1] = 5;
        break;
    }
    if (e->components == NULL) return -1;
    return 0;
}


typedef struct world_array{
    int cap;
    int size;
    entity *elements;
} world_array;

void init_world(world_array *arr, size_t length){
    arr->size = 0;
    arr->cap = length;
    arr->elements = (entity *) calloc(length, sizeof(*arr->elements));
    if (arr->elements == NULL) return; //Return some sort of error indicating this
}

void expand_world(world_array *arr, size_t add_size){ //Watch this function for memory bugs [weird outputs]
    arr->elements = (entity *) realloc(arr->elements, (arr->cap + add_size) * sizeof(*arr->elements));
    if (arr->elements != NULL) arr->cap += add_size;
}

int add_element(world_array *arr, entity *atlas, int id, float x, float y){
    if (arr->size + 1 >= arr->cap) expand_world(arr, 1);
    arr->elements[arr->size] = atlas[id];
    int err = init_entity(&arr->elements[arr->size], x, y);
    arr->size++;
    return err;
}

int remove_element(world_array *arr, int index){
    if (index < 0 || index > arr->size) return __OUT_OF_BOUNDS;
    arr->elements[index] = arr->elements[arr->size-1];
    arr->elements[arr->size-1] = (entity) {};
    arr->size -= 1;
    //Shrink if neccassary
    return 0;
}

void shrink_world(world_array *arr, size_t sub_size){
    arr->elements = (entity *) realloc(arr->elements, (arr->cap - sub_size) * sizeof(*arr->elements));
    arr->cap -= sub_size;

    if (arr->size == arr->cap) arr->size--;
}

void free_world(world_array *arr){
    for (int i = 0; i < arr->size; i++)
        free(arr->elements->components);
    
    free(arr->elements);
}
