#pragma once

typedef struct entity{
    unsigned int indicator : 4;
    unsigned char id;
    int src_idx; // Pointer may be faster, but uses more memory
    int component_idx;
    SDL_FRect sprite;
} entity;

typedef struct world_array{
    int cap, size;
    entity *elements;
    T
    // Perhaps Texture atlas ptr
}