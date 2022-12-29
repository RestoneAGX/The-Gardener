#pragma once

#define BitCheck(v,n) (v & (1 << n))
#define BitToggle(v,n) (v ^ (1 << n))
#define BitClear(v,n) (v & ~(1 << n))
#define BitSet(v,n) (v | (1 << n))

// TODO: Replace All lengths will the theoretical amount needed
#define ITEM_BUFF_LEN 60
#define ENTITY_BUFF_LEN 60
#define PROJECTILE_BUFF_LEN 255

typedef struct ItemBuffer {
    unsigned char current_idx;
    unsigned char id[ITEM_BUFF_LEN];
    unsigned char amount[ITEM_BUFF_LEN];
    SDL_Rect *src[ITEM_BUFF_LEN];
    SDL_FRect sprite[ITEM_BUFF_LEN];
}

typedef struct EntityBuffer {
    unsigned char id[ENTITY_BUFF_LEN];
    SDL_FRect sprite[ENTITY_BUFF_LEN];
    SDL_Rect *src[ENTITY_BUFF_LEN];
    unsigned char components[ENTITY_BUFF_LEN][3]; // TODO: 3 is a dummy value 
}

typedef struct ProjectileBuffer {
    unsigned int effects:4[PROJECTILE_BUFF_LEN];
    SDL_FRect sprite[PROJECTILE_BUFF_LEN];
    SDL_Rect *src[PROJECTILE_BUFF_LEN];
}

