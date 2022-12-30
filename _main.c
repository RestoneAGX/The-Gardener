#include "tools/Rendering.h"
#include "tools/Player_Systems.h"

#define W_HEIGHT 680
#define W_WIDTH 1048

int main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_EVERYTHING)) 
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
  int player_inputs[8] = {};
  SDL_Event event;

  init_textures(renderer);
  
  add_entity(&world, entity_presets, (W_WIDTH - 50) / 2, (W_HEIGHT - 50) / 2);

  switch_location(Dungeon, entity_presets); // REMOVE: this call after properly setting up the Hub and Dungeon Generation

  while (running)
  {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    handleInput(&event, &running, player_inputs);

    if (!game_state)
    {
        UpdateTimers();

        handlePlayerMovement(world.sprite, player_inputs); // TODO: Handle all players instead of just one
        // handleEnemies();

        render_game(renderer, player);
    }
    else
    {
      // handleInput_UI(&event,);
      // render_UI(renderer); 
    }
    
    SDL_RenderPresent(renderer);
    SDL_Delay(1000 / 60);
  }

  free_texture_buffers();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
 
  SDL_Quit();
  return 0;
}
