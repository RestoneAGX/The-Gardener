#pragma once
#include "ECS.h"
#include <SDL2/SDL.h>
#include "game_state.h"

#define Texture_Buffer_Length 20 // This will be replaced with the other atlas lengths

#define E_Width 20
#define E_Height 25

#define Tile_Atlas_Len 20
#define Entity_Atlas_Len 20
#define Item_Atlas_Len 20
#define UI_Atlas_Len 20

#define buffer_entry(i, width, height, src_x, src_y, base_w, base_h) \
(entity){.id = i,  .sprite = &(SDL_FRect) {.w  = width, .h = height}, &(SDL_Rect) {.x = base_w * src_x, .y = base_h * src_y, .w = base_w, .h = base_h}}

#define custom_entry(i, width, height, src_x, src_y, src_w, src_h) \
(entity){.id = i,  .sprite = &(SDL_FRect) {.w  = width, .h = height}, &(SDL_Rect) {.x = src_x, .y = src_y, .w = src_w, .h = src_h}}

SDL_Texture *entity_texture_atlas;
SDL_Texture *tile_texture_atlas;

entity entity_buffer[Entity_Atlas_Len] = {
    buffer_entry(0, 50, 65, 0, 0, E_Width, E_Height),
    buffer_entry(1, 50, 55, 1, 0, E_Width, E_Height),
    buffer_entry(2, 50, 55, 2, 0, E_Width, E_Height),
};

entity tile_buffer[Tile_Atlas_Len] = {
    buffer_entry(0, 30, 30, 0, 0, 30, 30),
    buffer_entry(0, 30, 30, 1, 0, 30, 30),
};

void render_players(entity plrs[3], SDL_Renderer *renderer)
{
    for (int i = 0; i < 3; i++)
        SDL_RenderCopyF(renderer, entity_texture_atlas, plrs[i].src, plrs[i].sprite);
}

void render_background(SDL_Renderer *renderer){
    for (int i = 0; i < 50; i++)
        SDL_RenderCopyF(renderer, tile_texture_atlas, background[i].src, background[i].sprite);
}

void render_world(SDL_Renderer *renderer)
{
    for (int i = 0; i < world.size; i++)
        SDL_RenderCopyF(renderer, entity_texture_atlas, world.elements[i].src, world.elements[i].sprite);
    // SDL_RenderCopyExF(renderer, entity_atlas, world.elements[i].src, world.elements[i].sprite, 0, NULL, SDL_FLIP_NONE); // Fill in the angle(0) with a value
}

void init_textures(SDL_Renderer *renderer)
{
    const char *name[4] = { // Fill the sheets in reverse (since the smaller sheets are ironically last)
        "Resources/entity_sheet.bmp",
        "Resources/Tile_Sheet.bmp",
        "Resources/Item_Sheet.bmp",
        "Resources/UI_Sheet.bmp",
    };

    for (int i = 0; i < 2; i++)
    { // Replace "< 2" with "< 4"
        SDL_Surface *image = SDL_LoadBMP(name[i]);
        SDL_Surface *optimized_image = SDL_ConvertSurface(image, image->format, 0);
        switch (i)
        {
        case 0:
            entity_texture_atlas = SDL_CreateTextureFromSurface(renderer, optimized_image);
            break;
        case 1:
            tile_texture_atlas = SDL_CreateTextureFromSurface(renderer, optimized_image);
            break;
        case 2:
            break;
        }

        SDL_FreeSurface(image); // REMOVE: if freeing must be done at the end of execution
        SDL_FreeSurface(optimized_image);
    }
}

void free_texture_buffers()
{
    SDL_DestroyTexture(tile_texture_atlas);
    SDL_DestroyTexture(entity_texture_atlas);
    // Destroy Item Texture Buffer
    // Destroy UI Texture Buffer
}