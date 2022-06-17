#pragma once
#include "ECS.h"
#include <SDL2/SDL.h>

#define Texture_Buffer_Length 20 //This will be replaced with the other atlas lengths

#define Sprite_Width 20
#define Sprite_Height 25

#define Background_Atlas_Len 20
#define Entity_Atlas_Len 20
#define Item_Atlas_Len 20
#define UI_Atlas_Len 20

SDL_Texture *entity_atlas;
SDL_Rect entity_atlas_pos[Entity_Atlas_Len] = {
    {0, 0, .w = Sprite_Width, .h = Sprite_Height},
    {Sprite_Width, 0, .w = Sprite_Width, .h = Sprite_Height},
};

entity atlas_buffer[Entity_Atlas_Len] = {
    (entity) {.id = 0, .sprite = &(SDL_FRect){.w = 50, .h = 65}},
    (entity) {.indicator = Renderable, .id = 1, .sprite = &(SDL_FRect){.w = 50, .h = 55}},
    (entity) {.indicator = Renderable | Item, .id = 1, .sprite = &(SDL_FRect){.w = 50, .h = 55}},
};

void render_players(entity plrs[3], SDL_Renderer *renderer){
    for (int i = 0; i < 3; i++)
        SDL_RenderCopyF(renderer, entity_atlas, &entity_atlas_pos[plrs[i].id], (plrs[i]).sprite);
        // SDL_RenderCopyExF(renderer, entity_atlas, &entity_atlas_pos[plrs[i].id], plrs[i].sprite, 90, NULL, SDL_FLIP_NONE);
}

void render_background(SDL_Renderer *renderer);

void render_world(SDL_Renderer *renderer){
    for (int i = 0; i < world.size; i++)
        SDL_RenderCopyF(renderer, entity_atlas, &entity_atlas_pos[world.elements[i].id], (world.elements + i)->sprite);
}

void init_textures(SDL_Renderer * renderer){
    const char *name[4] = {
        "entity_sheet.bmp",
        "UI_Sheet.bmp",
        "Tile_Sheet.bmp",
        "Item_Sheet.bmp",
    };

    for (int i = 0; i < 1; i++){ //Replace "< 1" with "< 3" 
        SDL_Surface *image = SDL_LoadBMP(name[i]);
        SDL_Surface *optimized_image = SDL_ConvertSurface(image, image->format, 0);
        entity_atlas = SDL_CreateTextureFromSurface(renderer, optimized_image);

        SDL_FreeSurface(image); // REMOVE: if freeing must be done at the end of execution
        SDL_FreeSurface(optimized_image);
    }
}

void free_texture_buffers(){
    SDL_DestroyTexture(entity_atlas);
    // Place UI, Tile and Item buffers here
}