#include "ECS.h"
#include <SDL2/SDL.h>

#define Interactable 0x1

#define current_UI_elements 1

typedef struct
{
    void *rect;
    void *content;
    void *function;
} button;

// For Clicking:
// get interaction
// -> Search through UI
// -> Check mouse pos against other UI objects
// --> If instance is within range -> Pass it's ID into interact with UI

// int interaction_idx = 0; // the index of the current interaction

void Interact(entity *UI_element)
{
    switch (UI_element->id)
    {
    default: // Button Default
        break;
    }
    // Check indicator (Determines if interactable and stuff)
    // Perform operation according to id (id can indicate if it is a button, slider, dropdown, etc)
}

void handleInput_UI(SDL_Event *event, int *game_active, world_array *UI)
{
    while (SDL_PollEvent(event))
    {
        if (event->type == SDL_QUIT)
            *game_active = 0;

        else if (event->type == SDL_MOUSEBUTTONDOWN)
        {
            if (event->button.button == SDL_BUTTON_LEFT)
            {
                for (int i = 0; i < UI->cap; i++)
                {
                    if (BitCheck(UI->elements[i].indicator, 0)) // Check if interactable
                    {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                    SDL_FRect *rPtr = UI->elements[i].sprite;

                        // NOTE: Implict conversion, but I have no idea how this will go
                    if (x >= rPtr->x && x <= rPtr->x + rPtr->w &&
                        y >= rPtr->y && y <= rPtr->y + rPtr->h)
                            Interact(UI->elements + i);
                    }
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