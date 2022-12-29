#pragma once
#include "game_state.h"
#include <math.h>

#define xPoint(sprite) ( sprite.x + sprite.y )
#define dist(spriteA, spriteB) (sqrt(                               \
    ( (spriteB.x - spriteA.x) * (spriteB.x - spriteA.x) ) + \
    ( (spriteB.y - spriteA.y) * (spriteB.y - spriteA.y) ) ) * 0.1)

void die(entity *target, int i) // TODO: Make the switch statement branchless
{
    switch (target->id) {
        case 0: // NOTE: Uncomment the ones below, they're DEMO changes
            // printf("Player Dead\n");
            break;
        case 1:
            printf("case 1, ");
        case 2: // Drop Inventoroy
            printf("2, ");
        case 3: // Drop a tomato seed
            printf ("3, ");
        default:
            printf("Now in your mom\n");
            remove_element(&world, i);
            break;
    }
}

int hitbox(entity *target, int i, entity *caller, float range)
{
    float distance = dist(target->sprite, caller->sprite);

    if ( distance <= range)
    {
        target->components[0] -= caller->components[1]; // TODO: Add def into Calculation
        if (target->components[0] < 1)
            die(target, i);
       
        return 1;
    }
    return 0;
}

void handleEnemies(entity *plr)
{ 
    for (int i = 0; i < world.size; i++)
    {
        // CHASING
        // int x_dir = ( world.elements[i].sprite.x < plr->sprite.x ) + 
                  ( ( world.elements[i].sprite.x > plr->sprite.x ) * -1 ); 
        // int y_dir = ( world.elements[i].sprite.y < plr->sprite.y ) + 
                  ( ( world.elements[i].sprite.y > plr->sprite.y ) * -1 );

        // world.elements[i].sprite.x += x_dir;
        // world.elements[i].sprite.y += y_dir;

        hitbox(plr, i, world.elements + i, 10);
    }
}
