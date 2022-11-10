#include "ECS.h"
#include <SDL2/SDL.h>

#define Interactable 0x1

#define Menus 1
#define Menu_Lens 3

typedef struct button
{
    unsigned char indicator : 4;
    SDL_FRect *rect;
    void (*func)();
    void *content;
} button;

button menus[Menus][Menu_Lens];
unsigned char active_menu = 0;

// For Clicking:
// get interaction
// -> Search through UI
// -> Check mouse pos against other UI objects
// --> If instance is within range -> Pass it's ID into interact with UI

void handleInput_UI(SDL_Event *event, int *game_active)
{
    while (SDL_PollEvent(event))
    {
        if (event->type == SDL_QUIT)
            *game_active = 0;

        else if (event->type == SDL_MOUSEBUTTONDOWN)
        {
            if (event->button.button == SDL_BUTTON_LEFT)
                for (int i = 0; i < Menu_Lens; i++){
                    if (BitCheck(menus[active_menu][i].indicator, 0)) // Check if interactable
                    {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        SDL_FRect *rPtr = menus[active_menu][i].rect;

                        if (x >= rPtr->x && x <= rPtr->x + rPtr->w && // NOTE: Implict conversion, but I have no idea how this will go
                            y >= rPtr->y && y <= rPtr->y + rPtr->h)
                                menus[active_menu][i].func(); // Possibly check indicator, if slider and things of that sort are implemented
                    }
                }

            // else if (event->button.button == SDL_BUTTON_RIGHT)
            // {
            //     if (event->type == SDL_MOUSEBUTTONDOWN)    {}
            //     else if (event->type == SDL_MOUSEBUTTONUP) {}
            // }
        }

        // else if (event->type == SDL_MOUSEBUTTONUP) {}
    }
}