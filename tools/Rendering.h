#include <SDL2/SDL.h>
#include "game_state.h"

#define E_Width 20
#define E_Height 25

#define Entity_Atlas_Len 20
#define Item_Atlas_Len 20
#define Tile_Atlas_Len 20
#define UI_Atlas_Len 20

#define buffer_entry(i, sprite_width, sprite_height, src_x, src_y, base_w, base_h)                                                                                 \
    (entity){ .id = i, .sprite = {.w = sprite_width, .h = sprite_height}, .src = &(SDL_Rect) { .x = base_w * src_x, .y = base_h * src_y, .w = base_w, .h = base_h } \
    }

enum {
  entity_texture_atlas,
  tile_texture_atlas,
  item_texture_atlas,
  UI_texture_atlas
};

SDL_Texture *texture_atlas[4];

entity entity_presets[Entity_Atlas_Len] = {
    buffer_entry(0, 50, 65, 0, 0, E_Width, E_Height),
    buffer_entry(1, 50, 65, 1, 0, E_Width, E_Height),
    buffer_entry(2, 50, 65, 2, 0, E_Width, E_Height),
    buffer_entry(3, 50, 50, 3, 0, E_Width, E_Height),
};

entity tile_presets[Tile_Atlas_Len] = {
    buffer_entry(0, 30, 30, 0, 0, 30, 30),
    buffer_entry(1, 30, 30, 1, 0, 30, 30),
};

void render_game(SDL_Renderer *renderer){
    // for (int i = 0; i < 50; i++) // Less than the max amount of background items
    //     SDL_RenderCopyF(renderer, texture_atlas[tile_texture_atlas], background[i].src, background[i].sprite);

    for (int i = 0; i < world.size; i++)
        SDL_RenderCopyF(renderer, texture_atlas[entity_texture_atlas], world.src[i], &world.sprite[i]);
    // SDL_RenderCopyExF(renderer, texture_atlas[entity_atlas], world.elements[i].src, world.elements[i].sprite, 0, NULL, SDL_FLIP_NONE); // Fill in the angle(0) with a value

    // for (int i = 0; i < items.size; i++)
    //     SDL_RenderCopyF(renderer, texture_atlas[item_texture_atlas], items.src[i], &items.sprite[i]);
}

/*
void render_UI(SDL_Renderer *renderer, entityBuffer*UI){
    for (int i = 0; i < UI->size; i++)
        SDL_RenderCopyF(renderer, texture_atlas[UI_texture_atlas], UI->elements[i].src, &UI->elements[i].sprite);
}
*/

void init_textures(SDL_Renderer *renderer)
{
    const char *name[4] = { // Fill the sheets in reverse (since the smaller sheets are ironically last)
        "Resources/entity_sheet.bmp",
        "Resources/Tile_Sheet.bmp",
        "Resources/Item_Sheet.bmp",
        "Resources/UI_Sheet.bmp",
    };

    for (int i = 0; i < 2; i++) // TODO: Replace "< 2" with "< 4"
    {
        SDL_Surface *image = SDL_LoadBMP(name[i]);
        SDL_Surface *optimized_image = SDL_ConvertSurface(image, image->format, 0);
        texture_atlas[i] = SDL_CreateTextureFromSurface(renderer, optimized_image);
        SDL_FreeSurface(image); // REMOVE: if freeing must be done at the end of execution
        SDL_FreeSurface(optimized_image);
    }
}

void free_texture_buffers()
{
    SDL_DestroyTexture(texture_atlas[entity_texture_atlas]);
    SDL_DestroyTexture(texture_atlas[tile_texture_atlas]);
    SDL_DestroyTexture(texture_atlas[item_texture_atlas]);
    SDL_DestroyTexture(texture_atlas[UI_texture_atlas]);
}
