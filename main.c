#include <stdio.h>
#include "tools/ECS.h"
#include <SDL2/SDL.h>
#include "Player_Funcs.h"

#define W_HEIGHT 680
#define W_WIDTH 1048

int main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) // Initializes the timer, audio, video, joystick, haptic, gamecontroller and events subsystems
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
  int directional_inputs[6] = {0, 0, 0, 0, 0, 0};
  SDL_Event event;


  entity player = (entity){.id = 0, .sprite = &(SDL_FRect){.x = (W_WIDTH - 50) / 2, .y = (W_HEIGHT - 50) / 2, .w = 50, .h = 65}};
  init_entity(&player);

  world_array world;
  init_world(&world, 1);
  add_element(&world, (entity) {.id = 1, .indicator = Renderable,.sprite = &(SDL_FRect){.x = (W_WIDTH - 50) / 2, .y = (W_HEIGHT - 50) / 2, .w = 50, .h = 50}});

  init_presets(renderer);
  while (running)
  {
    // UpdateTimers();
    handleInput(&event, &running, directional_inputs);
    handlePlayerMovement(player.sprite, directional_inputs);

    // Combat Sys
    // if (directional_inputs[5] == 1){//If Attacking
    //   for(int i = 0; i < world.size; i++){
    //   printf("Enemy HP: %d", world.elements[i].components[0]);
    //     if (BitCheck(world.elements[i].indicator, 1) == 0){
    //       if((char)world.elements[i].components[0] - 10 > 0)
    //         world.elements[i].components[0] -= 10;
    //       else
    //         world.elements[i].components[0] = 0;}
    //   printf("Enemy HP: %d", world.elements[i].components[0]);
    //   }
    // }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 128, 235, 255, 255);
    // SDL_RenderFillRectF(renderer, enemy.sprite);
    render_world(&world, renderer);

    SDL_RenderCopyF(renderer, texture_buffer[player.id], NULL, player.sprite);

    SDL_RenderPresent(renderer);
    SDL_Delay(1000 / 60);
  }

  free_texture_buffer();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}