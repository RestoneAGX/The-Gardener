#include<SDL2/SDL.h>
#include "ECS.h"
#include "Dungeon.h"

float target_time = 2;
Uint32 ref_time;

void enemy_generation(world_array *world, entity *atlas){
    if( (float) (SDL_GetTicks() - ref_time) / 1000 > target_time ) {
        ref_time = SDL_GetTicks();
        target_time = (float) generate_range(3, 12); 
        add_element(world, atlas + 2, generate_range(0, 1048), generate_range (0, 680));
    }
}

