#pragma once
#include "game_state.h"
#include <math.h>

#define xPoint(sprite) ( sprite.x + sprite.y )
#define dist(spriteA, spriteB) (sqrt(                               \
    ( (spriteB.x - spriteA.x) * (spriteB.x - spriteA.x) ) + \
    ( (spriteB.y - spriteA.y) * (spriteB.y - spriteA.y) ) ) * 0.1)

void die(int id, int i) // TODO: Make the switch statement branchless
{
    switch (id) {
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
            remove_entity(&world, i);
            break;
    }
}


int hitbox(int caller, int opp, float range)
{
    if ( dist(world.sprite[caller], world.sprite[opp]) <= range)
    {
        world.components[opp].Hp -= world.components[caller].Atk; // TODO: Add def into Calculation
        if (world.components[opp].Hp < 1)
            die(world.id[opp], opp);

        return 1;
    }
    return 0;
}

void handleEnemies()
{ 
    for (int i = 0; i < world.size; i++)
    {
        // CHASING
        // int x_dir = ( world.sprite[i].x < plr->sprite.x ) + 
        //          ( ( world.sprite[i].x > plr->sprite.x ) * -1 ); 
        // int y_dir = ( world.sprite[i].y < plr->sprite.y ) + 
        //          ( ( world.sprite[i].y > plr->sprite.y ) * -1 );

        // world.sprite[i].x += x_dir;
        // world.sprite[i].y += y_dir;

        hitbox(0, i, 10); // TODO: Loop over other players
    }
}
