#pragma once
#include<stdlib.h>
#include<SDL2/SDL.h>

#define BitCheck(v,n) (v & (1 << n))
#define BitToggle(v,n) (v ^ (1 << n))
#define BitClear(v,n) (v & ~(1 << n))
#define BitSet(v,n) (v | (1 << n))

typedef struct entity{
    unsigned int indicator : 4;
    unsigned int id : 8;
    SDL_FRect sprite;
    SDL_Rect *src;
    unsigned char *components;
} entity;

typedef struct world_array{
    int cap;
    int size;
    entity *elements;
} world_array;

void init_entity(entity *e, float x, float y){
    e->sprite.x = x;
    e->sprite.y = y;

    switch(e->id){ //Allocate memory according to ID
        case 3: 
        e->components = (unsigned char*) calloc (4, 1);
        e->components[0] = 255;
        break;

        case 2:
        case 1: // HP, Atk, Def, Speed //Also Place default stats
        case 0: e->components = (unsigned char*) calloc (10, 1); 
        e->components[0] = 255;
        e->components[1] = 5;
        break;
    }
}

void init_world(world_array *arr, size_t length){
    arr->size = 0;
    arr->cap = length;
    arr->elements = (entity *) calloc(length, sizeof(entity));
}

void add_element(world_array *arr, entity *atlas, float x, float y){
    arr->elements[arr->size] = *atlas;
    init_entity(arr->elements + arr->size, x, y);
    if (++arr->size >= arr->cap)
        arr->elements = (entity *) realloc(arr->elements, ++arr->cap * sizeof(*arr->elements)); // ++arr->cap might cause a problem
}

void remove_element(world_array *arr, int index){
    free(arr->elements[index].components);
    arr->elements[index] = arr->elements[arr->size];
    arr->elements[arr->size--] = (entity) {};
}

void free_world(world_array *arr){
    for (int i = 0; i < arr->size; i++)
        free((arr->elements+i)->components);
    
    free(arr->elements);
}
