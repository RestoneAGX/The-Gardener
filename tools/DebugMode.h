#include <SDL2/SDL.h>
#include "game_state.h"

int selected = 0;

void debugInput(SDL_Event *event, int *game_active){
    while(SDL_PollEvent(event)){
        if (event->type == SDL_QUIT) *game_active = 0;

        else if(event->button.button == SDL_BUTTON_LEFT){
            if (event->type == SDL_MOUSEBUTTONDOWN){
                int x, y;
                SDL_GetMouseState(&x, &y);
                background[0] = tile_buffer[selected];
                background[0].sprite->x = x;
                background[0].sprite->y = y;
                // add_element(&world, tile_buffer, selected, x, y);
                // Set the block
            }
        }

        else if(event->button.button == SDL_BUTTON_RIGHT){
            if (event->type == SDL_MOUSEBUTTONDOWN){
                // Clear the block
            }
        }

        else if (event->type == SDL_KEYUP){
            switch(event->key.keysym.scancode){
                case SDL_SCANCODE_SPACE: DebugMode = !DebugMode;
                break;
                default:
                break;
            }
        }
    }
}