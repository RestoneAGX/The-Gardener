#pragma once
#include "game_state.h"

#define xPoint(sprite) ( sprite.x + sprite.y + ( (sprite.w + sprite.h) * 0.5 ) )

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

void hitbox(entity *target, int i, int dmg, float hit_point, float range)
{
    float target_point = xPoint(target->sprite);

    if (fabs(hit_point - target_point) <= range)
    {
        printf("Enemy HP: %i, Distance: %f\n", target->components[0], fabs(target_point - hit_point));

        if ((int) target->components[0] - dmg > 0)
            target->components[0] -= dmg; // TODO: Maybe add defense calculation
        else
            die(target, i);
    }
}

void handleEnemies(entity *plr)
{ 
    for (int i = 0; i < world.size; i++)
    {
        int x_dir = ( world.elements[i].sprite.x < plr->sprite.x ) + 
                  ( ( world.elements[i].sprite.x > plr->sprite.x ) * -1 ); 
        int y_dir = ( world.elements[i].sprite.y < plr->sprite.y ) + 
                  ( ( world.elements[i].sprite.y > plr->sprite.y ) * -1 );

        // world.elements[i].sprite.x += x_dir;
        // world.elements[i].sprite.y += y_dir;

        float target_point = xPoint(world.elements[i].sprite); 
   

        hitbox(plr, i, 10, target_point, 50);
        /*
        if (BitCheck(world.elements[i].indicator, 0))
        {
            // Start Chasing the player
        }

        if (BitCheck(world.elements[i].indicator, 1))
        {
            // Shoot the player for a bit
            // Teleport to a random place (either in a circle around the player or just around the room)
            // Use the vals in components to determine things like how often they shoot, how many things they shoot, what things they shoot, and what pattern they follow the player
        }
        */
    }
}
