#include "Systems.h"
#include "Storage_System.h"

#define Timer_len 3
#define atk_range 10

enum inputs { Left, Right, Up, Down, Dash, Atk, Side, Ult };

unsigned char cooldowns = 0; // bits: 1 -> dash; 2 -> atk;

Uint32 timer[Timer_len] = {};
float timer_max[Timer_len] = {.75, .25, .5};

void UpdateTimers() {
  for (int i = 0; i < Timer_len; i++)
    if (BitCheck(cooldowns, i)) {
      if (!timer[i])
        timer[i] = SDL_GetTicks();
      else if ( (float) (SDL_GetTicks() - timer[i]) / 1000 >= timer_max[i]) {
        cooldowns = BitClear(cooldowns, i);
        timer[i] = 0;
      }
    }
}

void handleCombat() {
  // if (isAtk) {
  //   if (inventory[1] > 1){
  //   inventory[1]--;
  //   }
  // } else {
  //   cooldowns = BitSet(cooldowns, 2);
  // }

  for (int i = 1; i < world.size; i++) // Replace: 1 with the expected multiplayer [2 || 4]
    hitbox(0, i, atk_range);
}

#define DeltaTime 60
#define DashForce  7175
#define pSpeed 7

float velocity = 0;
float dash_time = 0;

void handlePlayerMovement(SDL_FRect *p_sprite, int *directional_inputs) {
  int xDir = (-directional_inputs[Left] + directional_inputs[Right]);
  int yDir = (-directional_inputs[Up] + directional_inputs[Down]);

  if (directional_inputs[Dash]) {
    cooldowns = BitSet(cooldowns, 0);
    
    dash_time += 0.1;
    velocity += DashForce / (DeltaTime * DeltaTime);
    velocity -= dash_time;

    if (velocity < 0){
        directional_inputs[Dash] = 0;
        velocity = 0;
        dash_time = 0;
        handleCombat(); 
    }

    p_sprite->x += xDir * velocity * pSpeed;
    p_sprite->y += yDir * velocity * pSpeed;
  }

  p_sprite->x += (-directional_inputs[Left] + directional_inputs[Right]) * pSpeed;
  p_sprite->y += (-directional_inputs[Up] + directional_inputs[Down]) * pSpeed;

#define screen_width (1048 - p_sprite->w)
  // Collision
  p_sprite->x = (int) p_sprite->x & ( (p_sprite->x < 0) - 1 );
  p_sprite->y = (int) p_sprite->y & ( (p_sprite->y < 0) - 1 );
  if (p_sprite->y > 680 - p_sprite->h)
    p_sprite->y = 680 - p_sprite->h; // Screen width
}

void handleInput(SDL_Event *event, int *game_active, int *keyInput) {
  while (SDL_PollEvent(event))
    switch(event->type){
        case SDL_MOUSEBUTTONDOWN:
            keyInput[Dash] = ( !BitCheck(cooldowns, 0) ) & ( event->button.button == SDL_BUTTON_RIGHT );
            handleCombat();
            // handleItems(plr); // TODO: Perhaps make this automatically go into your inventory, while also having a menu showing all dropped loot through the dungeon. You can choose what you will keep and what you will toss
            break;
        case SDL_QUIT: *game_active = 0;
            break;
        case SDL_KEYDOWN:
            switch (event->key.keysym.scancode) {
            case SDL_SCANCODE_LEFT:
            case SDL_SCANCODE_A:
                keyInput[Left] = 1;
                break;

            case SDL_SCANCODE_RIGHT:
            case SDL_SCANCODE_D:
                keyInput[Right] = 1;
                break;

            case SDL_SCANCODE_UP:
            case SDL_SCANCODE_W:
                keyInput[Up] = 1;
                break;

            case SDL_SCANCODE_DOWN:
            case SDL_SCANCODE_S:
                keyInput[Down] = 1;
                break;

            case SDL_SCANCODE_LSHIFT:
                keyInput[Dash] = 1;
                break;

            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event->key.keysym.scancode) {
            case SDL_SCANCODE_LEFT:
            case SDL_SCANCODE_A:
              keyInput[Left] = 0;
              break;

            case SDL_SCANCODE_RIGHT:
            case SDL_SCANCODE_D:
              keyInput[Right] = 0;
              break;

            case SDL_SCANCODE_UP:
            case SDL_SCANCODE_W:
              keyInput[Up] = 0;
              break;

            case SDL_SCANCODE_DOWN:
            case SDL_SCANCODE_S:
              keyInput[Down] = 0;
              break;

            case SDL_SCANCODE_F: // Activate Ultimate
              break;

            case SDL_SCANCODE_Q: 
              game_state = !game_state;
              break;

            case SDL_SCANCODE_SPACE:
                switch_location(game_location +1, entity_presets);
              break;
            default:
                break;
            }
            break;
        default:
            break;
    }
}
