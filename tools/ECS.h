#pragma once
#include<stdlib.h>
#include<SDL2/SDL.h>

#define BitCheck(v,n) (v & (1 << n))
#define BitToggle(v,n) (v ^ (1 << n))
#define BitClear(v,n) (v & ~(1 << n))
#define BitSet(v,n) (v | (1 << n))

#define __OUT_OF_BOUNDS -2;
#define Texture_Buffer_Length 20

#define Renderable 0x1
#define Item 0x2

void *texture_buffer[Texture_Buffer_Length];

typedef struct entity{
    unsigned int indicator : 4;
    unsigned int id;
    unsigned char *components;
    void * sprite;
} entity;

int init_entity(entity* e);

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

int add_element(world_array *arr, entity newValue){
    if (arr->size + 1> arr->cap) expand_world(arr, 1);

    arr->elements[arr->size] = newValue;
    int err = init_entity(&arr->elements[arr->size]);
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

void render_world(world_array *arr, SDL_Renderer *renderer){
    for (int i = 0; i < arr->size; i++)
        SDL_RenderCopyF(renderer, texture_buffer[(arr->elements + i)->id], NULL, (arr->elements + i)->sprite);
    // This may cause unexpect behavior due to a lack of testing and possibly weird pointer arithmatic
}

int init_entity(entity *e){
    switch(e->id){
        case 1: e->components = (unsigned char*) calloc(4, 1); // HP, Atk, Def, Speed //Also Place default stats
        e->components[0] = 20;
        break;
        case 0: e->components = (unsigned char*) calloc(10, 1); //Allocate memory according to ID
        break;
    }
    if (e->components == NULL) return -1;
    return 0;
}

void init_presets(void * renderer){
    SDL_Surface *image = SDL_LoadBMP("cocoa.bmp");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);

    // SDL_Surface *vil_img = SDL_LoadBMP("Vanilla.bmp");
    // SDL_Texture *vil_txt = SDL_CreateTextureFromSurface(renderer, vil_img);

    texture_buffer[0] = texture;
    texture_buffer[1] = texture;
    SDL_FreeSurface(image); // REMOVE: if freeing must be done at the end of execution
}

void free_texture_buffer(){
    for (int i = 0; i < Texture_Buffer_Length; i++)
        SDL_DestroyTexture(texture_buffer[i]);
}