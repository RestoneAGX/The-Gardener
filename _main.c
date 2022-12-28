#include "tools/Rendering.h"
#include "tools/Demo_System.h" // REMOVE: after finishing the 1 week demo
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
  int player_inputs[7] = {0, 0, 0, 0, 0, 0, 0};
  SDL_Event event;

  init_textures(renderer);
  
  entity player[3];
  player[0] = entity_buffer[0]; // Enhance array when multiplayer is added
  init_entity(player, (W_WIDTH - 50) / 2, (W_HEIGHT - 50) / 2);

  switch_location(Dungeon, entity_buffer); // REMOVE: this call after properly setting up the Hub and Dungeon Generation

  while (running)
  {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    handleInput(&event, player, &running, player_inputs); //TODO: fix crashing bug here

    if (!game_state)
    {
        UpdateTimers();
        // enemy_generation(&world, entity_buffer);
        // DEBUG
        printf("Distance: %f\n", dist(player[0].sprite, world.elements[0].sprite));

        handlePlayerMovement(&player[0].sprite, player_inputs); // TODO: Handle all players instead of just one
        handleEnemies(player);

        render_game(renderer, player);
    }
    else
    {
      // handleInput_UI(&event,);
      // render_UI(renderer); //TODO: Write UI rendering
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
