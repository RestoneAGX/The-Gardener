#pragma once
#include "ECS.h"
#include <SDL2/SDL.h>

#define Texture_Buffer_Length 20
#define Atlas_Length 20

SDL_Texture *texture_buffer[Texture_Buffer_Length];

entity atlas_buffer[Atlas_Length] = {
    (entity) {.id = 0, .sprite = &(SDL_FRect){.w = 50, .h = 65}},
    (entity) {.indicator = Renderable, .id = 1, .sprite = &(SDL_FRect){.w = 50, .h = 50}},
};

void render_players(entity *plrs, SDL_Renderer *renderer){
    for (int i = 0; i < 3; i++)
        SDL_RenderCopyF(renderer, texture_buffer[(plrs[i]).id], NULL, (plrs[i]).sprite);
}

void render_world(world_array *arr, SDL_Renderer *renderer){ // hacky solution using pointer arithmatic, WATCH OUT!!!
    for (int i = 0; i < arr->size; i++)
        SDL_RenderCopyF(renderer, texture_buffer[(arr->elements + i)->id], NULL, (arr->elements + i)->sprite);
}

void init_textures(SDL_Renderer * renderer){
    const char *names[ ] =
    {
        "cocoa.bmp",
        "vanilla.bmp",
    };

    for (int i = 0; i < 2; i++){
        SDL_Surface *image = SDL_LoadBMP(names[i]);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);

        texture_buffer[i] = texture;
        SDL_FreeSurface(image); // REMOVE: if freeing must be done at the end of execution
    }
}

void free_texture_buffer(){
    for (int i = 0; i < Texture_Buffer_Length; i++)
        SDL_DestroyTexture(texture_buffer[i]);
    // I'm surprised this doesn't have unexpected behavior yet
}