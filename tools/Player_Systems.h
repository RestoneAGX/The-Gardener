#include "Systems.h"
#include "Storage_System.h"

#define Timer_len 3
#define atk_range 10

enum inputs { Left, Right, Up, Down, Dash, Atk, Side, Ult };

unsigned char cooldowns = 0; // bits: 1 -> dash; 2 -> atk; 3 -> side;

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

void handlePlayerMovement(SDL_FRect *p_sprite, int *directional_inputs) {
  int speed = 7;

  if (directional_inputs[Dash] > 0 && BitCheck(cooldowns, 0) == 0) {
    speed = 100;
    cooldowns = BitSet(cooldowns, 0);
  }

  p_sprite->x += (-directional_inputs[Left] + directional_inputs[Right]) * speed;
  p_sprite->y += (-directional_inputs[Up] + directional_inputs[Down]) * speed;

  // Collision
  if (p_sprite->x < 0)
    p_sprite->x = 0;
  if (p_sprite->x > 1048 - p_sprite->w)
    p_sprite->x = 1048 - p_sprite->w; // Screen width

  if (p_sprite->y < 0)
    p_sprite->y = 0;
  if (p_sprite->y > 680 - p_sprite->h)
    p_sprite->y = 680 - p_sprite->h; // Screen width
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

// NOTE: Replace with a menu to select all non-seed items (or things that were not filled)
// void handleItems(entity *plr) {
//   int pPoint = xPoint(plr->sprite);
//   for (int i = ITEM_BUFFER_LEN; i > -1 ; i -= 2) {
//     int iPoint = xPoint(item_buffer[i].sprite);
//     if (abs(pPoint - iPoint) <= 50){
//       add_item(inventory, Inventory_Slots, item_buffer[i].id, item_buffer[i].amount);
//       item_buffer[i] = item_buffer[item_buff_size--]; // TODO: check if this works as expectedt
//     }
//   }
// }

void handleInput(SDL_Event *event, int *game_active, int *keyInput) {
  while (SDL_PollEvent(event))
    switch(event->type){
        case SDL_MOUSEBUTTONDOWN:
            // TODO: Maybe add cooldowns
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

            case SDL_SCANCODE_LSHIFT:
              keyInput[Dash] = 0;
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