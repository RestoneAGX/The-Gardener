#include <SDL2/SDL.h>


void debugInput(SDL_Event *event, int *game_active){
    while(SDL_PollEvent(event)){
        if (event->type == SDL_QUIT) *game_active = 0;

        else if(event->button.button == SDL_BUTTON_LEFT){
            if (event->type == SDL_MOUSEBUTTONDOWN){
                // Set the block
            }
        }

        else if(event->button.button == SDL_BUTTON_RIGHT){
            if (event->type == SDL_MOUSEBUTTONDOWN){
                // Clear the block
            }
        }
    }
}