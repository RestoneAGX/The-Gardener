#include <SDL2/SDL.h>
#include "tools/ECS.h"
#include "game_state.h"
#include "tools/Rendering.h"

#define Timer_len 3
#define atk_range 65

enum inputs{Left, Right, Up, Down, Dash, Atk, Side};

unsigned char cooldowns = 0; // bits: 1 -> dash; 2 -> atk;

Uint32 timer[Timer_len] = {};
float timer_max[Timer_len] = {.75, .25, 2};

void UpdateTimers(){
  for (int i = 0; i < Timer_len; i++){
    if (BitCheck(cooldowns, i)){
      if (!timer[i]){
        timer[i] = SDL_GetTicks();
      }
      else if((float) (SDL_GetTicks() - timer[i]) / 1000 >= timer_max[i]){
        cooldowns = BitClear(cooldowns, i);
        timer[i] = 0;
      }
    }
  }
}

void handleInput(SDL_Event *event, int *game_active, int *keyInput)
{
  while (SDL_PollEvent(event))
    if (event->type == SDL_QUIT) *game_active = 0;

    else if(event->button.button == SDL_BUTTON_LEFT) {
      if (event->type == SDL_MOUSEBUTTONDOWN) keyInput[Atk] = 1;
      else if(event->type == SDL_MOUSEBUTTONUP) keyInput[Atk] = 0;
    }
    
    else if(event->button.button == SDL_BUTTON_RIGHT) {
      if (event->type == SDL_MOUSEBUTTONDOWN) keyInput[Side] = 1;
      else if(event->type == SDL_MOUSEBUTTONUP) keyInput[Side] = 0;
    }

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

      default:
        break;
      }

    // printf("left: %d, Right: %d, Up: %d, Down: %d\n", keyInput[0], keyInput[1], keyInput[2], keyInput[3]);
}

void handlePlayerMovement(SDL_FRect *p_sprite, int *directional_inputs)
{
  int speed = 3;

  if(directional_inputs[Dash] > 0 && BitCheck(cooldowns, 0) == 0){
    speed = 100;
    cooldowns = BitSet(cooldowns, 0);
  }

  p_sprite->x += (-directional_inputs[Left] + directional_inputs[Right]) * speed;
  p_sprite->y += (-directional_inputs[Up] + directional_inputs[Down]) * speed;
}


void handleCombat(entity* plr, int *inputs){
  if (inputs[Atk] || inputs[Side]){
    for(int i = 0; i < world.size; i++)
      if (BitCheck(world.elements[i].indicator, 1) == 0 && (BitCheck(cooldowns, 1) || BitCheck(cooldowns, 2)) == 0){
          float ePoint = world.elements[i].sprite->x + world.elements[i].sprite->y;
          float pPoint;
          
          if (inputs[Atk]){
            int x, y;
            SDL_GetMouseState(&x, &y);
            pPoint = x+y;
            cooldowns = BitSet(cooldowns, 1);
          }else{
            pPoint = plr->sprite->x + plr->sprite->y;
            cooldowns = BitSet(cooldowns, 2);
          }

          printf("Enemy Point: %f, Player Point: %f, distance: %i\n", ePoint, pPoint, abs(ePoint - pPoint));

          hitbox(world.elements + i, i, plr->components[1], pPoint, atk_range);
      }else{
        add_item(inventory, Inventory_Slots, world.elements[i].id, world.elements[i].components[0]);
      }
  }
}