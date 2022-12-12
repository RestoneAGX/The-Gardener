#include "Systems.h"
#include "Storage_System.h"

#define Timer_len 3
#define atk_range 30

enum inputs { Left, Right, Up, Down, Dash, Atk, Side };

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

  p_sprite->x +=
      (-directional_inputs[Left] + directional_inputs[Right]) * speed;
  p_sprite->y += (-directional_inputs[Up] + directional_inputs[Down]) * speed;

  // Collision
  if (p_sprite->x < 0)
    p_sprite->x = 0;
  if (p_sprite->x > 948 - p_sprite->w)
    p_sprite->x = 948 - p_sprite->w; // Screen width

  if (p_sprite->y < 0)
    p_sprite->y = 0;
  if (p_sprite->y > 680 - p_sprite->h)
    p_sprite->y = 680 - p_sprite->h; // Screen width
}

void handleCombat(entity *plr, unsigned char isAtk) {
  int pPoint;
  if (isAtk) {
    // if (inventory[1] > 1){
    int x, y;
    SDL_GetMouseState(&x, &y);
    pPoint = x + y;

    inventory[1]--;
    // printf("Inventory Seeds: %i\n", inventory[0]);
    // }
  } else {
    pPoint = xPoint(plr->sprite);
    cooldowns = BitSet(cooldowns, 2);
  }

  for (int i = 0; i < world.size; i++)
    hitbox(world.elements + i, i, plr->components[1], pPoint, atk_range);

  printf("HP: %d\n", (int) plr->components[0]);
}

void handleItems(entity *plr) {
  
  int pPoint = xPoint(plr->sprite);
  for (int i = ITEM_BUFFER_LEN; i > -1 ; i -= 2) {
    int iPoint = xPoint(item_buffer[i].sprite);
    if (abs(pPoint - iPoint) <= 50){
      add_item(inventory, Inventory_Slots, item_buffer[i].id, item_buffer[i].amount);
      item_buffer[i] = item_buffer[item_buff_size--]; // TODO: check if this works as expectedt
    }
  }
}

void handleInput(SDL_Event *event, entity * plr, int *game_active, int *keyInput) {
  while (SDL_PollEvent(event))
    if (event->type == SDL_QUIT)
      *game_active = 0;

    else if (event->button.button == SDL_BUTTON_LEFT) {
      // if (event->type == SDL_MOUSEBUTTONDOWN && !BitCheck(cooldowns, 1)){
            handleCombat(plr, 1);
            handleItems(plr); 
      //  }
    }

    else if (event->button.button == SDL_BUTTON_RIGHT) {
      // if (event->type == SDL_MOUSEBUTTONDOWN && BitCheck(cooldowns, 2) == 0)
        if (BitCheck(cooldowns, 2) == 0)
            handleCombat(plr, 0);
    }

    else if (event->type == SDL_KEYDOWN)
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

    else if (event->type == SDL_KEYUP)
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
        // Inventory_Active = !Inventory_Active; //Toggle inventory
        game_state = !game_state;
        break;

      case SDL_SCANCODE_SPACE:
        inventory[1] = 5;
        // DISABLE FOR DEMO
        // switch_location(game_location +1, entity_buffer);
        break;

      default:
        break;
      }

  // printf("left: %d, Right: %d, Up: %d, Down: %d\n", keyInput[0], keyInput[1], keyInput[2], keyInput[3]);
}

