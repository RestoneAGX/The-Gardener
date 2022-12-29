#pragma once
#include<SDL2/SDL.h>

#define BitCheck(v,n) (v & (1 << n))
#define BitToggle(v,n) (v ^ (1 << n))
#define BitClear(v,n) (v & ~(1 << n))
#define BitSet(v,n) (v | (1 << n))

// REPLACE: lengths with the theoretical amount needed
#define ITEM_BUFF_LEN 60
#define ENTITY_BUFF_LEN 60
#define PROJECTILE_BUFF_LEN 255

typedef struct itemBuffer {
    unsigned char current_idx;
    unsigned char id[ITEM_BUFF_LEN];
    unsigned char amount[ITEM_BUFF_LEN];
    SDL_Rect *src[ITEM_BUFF_LEN];
    SDL_FRect sprite[ITEM_BUFF_LEN];
}itemBuffer;

typedef struct Components { unsigned char Hp, Atk, Def, x, y; } Components;

typedef struct entityBuffer {
    unsigned char current_idx;
    unsigned char id[ENTITY_BUFF_LEN];
    SDL_Rect *src[ENTITY_BUFF_LEN];
    Components components[ENTITY_BUFF_LEN]; 
    SDL_FRect sprite[ENTITY_BUFF_LEN];
}entityBuffer;

typedef struct projectileBuffer {
    unsigned char current_idx;
    unsigned char id[PROJECTILE_BUFF_LEN];
    unsigned char effects[PROJECTILE_BUFF_LEN];
    SDL_Rect *src[PROJECTILE_BUFF_LEN];
    SDL_FRect sprite[PROJECTILE_BUFF_LEN];
}projectileBuffer;

typedef struct item{
   unsigned char id;
   unsigned char amount;
   SDL_Rect *src;
   SDL_FRect sprite; 
}item;

typedef struct entity{
    unsigned char id;
    SDL_Rect *src;
    Components components;
    SDL_FRect sprite;
}entity;

typedef struct projectile {
    unsigned char id;
    unsigned char effects;
    SDL_Rect *src;
    SDL_FRect sprite;
}projectile;

#define cIdx buff->current_idx
#define BUFFER_FUNCS(val, sp_case, reverse_sp_case) \
void add_##val (val##Buffer* buff, val * val##_presets, unsigned char id){ \
    buff->id[cIdx] = id; \
    buff->src[cIdx] = val##_presets[id].src; \
    buff->sprite[cIdx++] = val##_presets[id].sprite; \
    sp_case; \
} \
void remove_##val (val##Buffer* buff, unsigned char idx){ \
    buff->id[idx] = buff->id[--cIdx]; \
    buff->src[idx] = buff->src[cIdx]; \
    buff->sprite[idx] = buff->sprite[cIdx]; \
    reverse_sp_case; \
}


BUFFER_FUNCS(item,
             buff->amount[cIdx] = item_presets[id].amount,
             buff->amount[idx] = buff->amount[cIdx])

BUFFER_FUNCS(entity, 
             buff->components[cIdx] = entity_presets[id].components,
             buff->components[idx] = buff->components[cIdx])

BUFFER_FUNCS(projectile, , )
