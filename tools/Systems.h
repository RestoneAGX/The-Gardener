#pragma once
#include <stdio.h>
#include "game_state.h"

void enemy_loot(int id)
{
    switch (id)
    {
    case 3:
        // Drop a tomato seed
        break;
    case 2:
    case 1:
    case 0: // Drop Inventory
    break;
    default:
        break;
    }
}

void die(entity *target, int i)
{
    if (target->id == 0) // TODO: change "==1" -> "< 3"
    {
        // Kill Player
    }
    else
    {
        enemy_loot(target->id);
        remove_element(&world, i);
    }
}

void hitbox(entity *target, int i, int dmg, float hit_point, float range)
{
    float target_point = xPoint(target->sprite);

    if (abs(target_point - hit_point) <= range)
    {
        printf("Enemy HP: %i, Distance: %d\n", target->components[0], abs(target_point - hit_point));

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

        world.elements[i].sprite.x += x_dir; // NOTE: 30 is a temp speed
        world.elements[i].sprite.y += y_dir;

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
