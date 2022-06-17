#include <stdio.h>
#include <SDL2/SDL.h>
#include "tools/ECS.h"
#include "tools/Player_Funcs.h"
#include "tools/Rendering.h"
#include "tools/DebugMode.h"

#define W_HEIGHT 680
#define W_WIDTH 1048

int main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_EVERYTHING)) // Initializes the timer, audio, video, joystick, haptic, gamecontroller and events subsystems
  {
    printf("Error initializing SDL: %s\n", SDL_GetError());
    return -1;
  }

  SDL_Window *window = SDL_CreateWindow("The Gardener", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, 0);
  if (!window)
  {
    printf("Error creating window: %s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer)
  {
    printf("Error creating renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  int running = 1;
  SDL_Event event;
  int player_inputs[7] = {0, 0, 0, 0, 0, 0, 0};

  init_storage();
  init_textures(renderer);

  entity player[3];
  player[0] = atlas_buffer[0]; // Put into an array for multiplayer purposes
  init_entity(&player[0], (W_WIDTH - 50) / 2, (W_HEIGHT - 50) / 2);

  init_world(&world, 1);

  add_element(&world, atlas_buffer, 1, (W_WIDTH - 50) / 2, (W_HEIGHT - 50) / 2); // TODO: Do error handling later.

  game_location = Dungeon; //TODO: REMOVE after shfiting base location to Dungeon

  while (running)
  {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 128, 235, 255, 100);
    if (!DebugMode)
    {
      handleInput(&event, &running, player_inputs);

      if (!game_state)
      {

        UpdateTimers();

        // Handle all players when multiplayer is added
        handlePlayerMovement(player[0].sprite, player_inputs);
        handleCombat(&player[0], player_inputs);

        render_world(renderer);
        // TODO: Render Items here
        render_players(player, renderer);
      }
      else
      {
        // TODO: Render UI here
      }
    }else{
      debugInput(&event, &running);
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(1000 / 60);
  }

  free_world(&world);
  free_texture_buffers();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}