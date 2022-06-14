#include <SDL2/SDL.h>
#include "tools/ECS.h"
#include "game_state.h"

enum inputs{Left, Right, Up, Down, Dash, Atk};

unsigned char cooldowns = 0; // bits: 1 -> dash; 2 -> ?

void UpdateTimers(); //TODO: Add cooldowns here


void handleInput(SDL_Event *event, int *game_active, int *keyInput)
{
  while (SDL_PollEvent(event))
    if (event->type == SDL_QUIT) *game_active = 0;

    else if (event->type == SDL_KEYDOWN)
      switch (event->key.keysym.scancode) {
      case SDL_SCANCODE_LEFT:
      case SDL_SCANCODE_A: keyInput[Left] = 1;
        break;

      case SDL_SCANCODE_RIGHT:
      case SDL_SCANCODE_D: keyInput[Right] = 1;
        break;

      case SDL_SCANCODE_UP:
      case SDL_SCANCODE_W: keyInput[Up] = 1;
        break;

      case SDL_SCANCODE_DOWN:
      case SDL_SCANCODE_S: keyInput[Down] = 1;
        break;

      case SDL_SCANCODE_LSHIFT: keyInput[Dash] = 1;
        break;

      case SDL_SCANCODE_SPACE: keyInput[Atk] = 1;
        break;

      default:
        break;
      }

    else if (event->type == SDL_KEYUP)
      switch (event->key.keysym.scancode) {
      case SDL_SCANCODE_LEFT:
      case SDL_SCANCODE_A: keyInput[Left] = 0;
        break;

      case SDL_SCANCODE_RIGHT:
      case SDL_SCANCODE_D: keyInput[Right] = 0;
        break;

      case SDL_SCANCODE_UP:
      case SDL_SCANCODE_W: keyInput[Up] = 0;
        break;

      case SDL_SCANCODE_DOWN:
      case SDL_SCANCODE_S: keyInput[Down] = 0;
        break;

      case SDL_SCANCODE_LSHIFT: keyInput[Dash] = 0;
      break;

      case SDL_SCANCODE_SPACE: keyInput[Atk] = 0;
       break;

      default:
        break;
      }

    // printf("left: %d, Right: %d, Up: %d, Down: %d\n", keyInput[0], keyInput[1], keyInput[2], keyInput[3]);
}

void handlePlayerMovement(SDL_FRect *p_sprite, int *directional_inputs)
{
  int speed = 3;

  if(directional_inputs[Dash] > 0 && BitCheck(cooldowns, 0)){
    speed = 15;
    cooldowns = BitClear(cooldowns, 0);
  }

  speed = (directional_inputs[Dash] > 0) ? 15 : 3;

  p_sprite->x += (-directional_inputs[Left] + directional_inputs[Right]) * speed;
  p_sprite->y += (-directional_inputs[Up] + directional_inputs[Down]) * speed;
}

void handleCombat(world_array* world, int *inputs){
  if (inputs[5] == 1){//If Attacking
    for(int i = 0; i < world->size; i++)
      if (BitCheck(world->elements[i].indicator, 1) == 0){
        if((char)world->elements[i].components[0] - 10 > 0)
          world->elements[i].components[0] -= 10;
        else
          remove_element(world, i);
      }else{
        add_item(inventory, Inventory_Slots, world->elements[i].id, world->elements[i].components[0]);
      }
    }
}