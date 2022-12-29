#pragma once

#define BitCheck(v,n) (v & (1 << n))
#define BitToggle(v,n) (v ^ (1 << n))
#define BitClear(v,n) (v & ~(1 << n))
#define BitSet(v,n) (v | (1 << n))

// REPLACE: lengths with the theoretical amount needed
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

typedef struct Components { unsigned char Hp, Atk, Def, x, y } components;

typedef struct EntityBuffer {
    unsigned char current_idx;
    unsigned char id[ENTITY_BUFF_LEN];
    SDL_Rect *src[ENTITY_BUFF_LEN];
    Components components[ENTITY_BUFF_LEN]; 
    SDL_FRect sprite[ENTITY_BUFF_LEN];
}

typedef struct ProjectileBuffer {
    unsigned char current_idx;
    unsigned char effects[PROJECTILE_BUFF_LEN];
    SDL_Rect *src[PROJECTILE_BUFF_LEN];
    SDL_FRect sprite[PROJECTILE_BUFF_LEN];
}

typedef struct item{
   unsigned char id;
   unsigned char amount;
   SDL_Rect *src;
   SDL_FRect sprite; 
}
typedef struct entity{
    unsigned char id;
    SDL_Rect *src;
    Components components;
    SDL_FRect sprite;
}

typedef struct projectile {
    unsigned char effects;
    SDL_Rect *src;
    SDL_FRect sprite;
}

#define cIdx buff->current_idx
void add_entity(EntityBuffer* buff, entity* entity_presets, unsigned char id){
    buff->id[cIdx] = id;
    buff->src[cIdx] = entity_presets[id].src;
    buff->components[cIdx] = entity_presets[id].components;
    buff->sprite[cIdx++] = entity_presets[id].sprite;
}

void remove_entity(EntityBuffer* buff, unsigned char idx){
    buff->id[idx] = buff->id[--cIdx];
    buff->src[idx] = buff->src[cIdx];
    buff->components[idx] = buff->components[cIdx];
    buff->sprite[idx] = buff->sprite[cIdx];
}
