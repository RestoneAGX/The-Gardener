#pragma once
#include <stdio.h>
#include "Game_State.h"

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
    if (target->id < 3)
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
    float target_point = target->sprite->x + target->sprite->y + ((target->sprite->w + target->sprite->h) / 2);

    if (abs(target_point - hit_point) <= range)
    {
        printf("Enemy HP: %i, ", target->components[0]);

        if ((int) target->components[0] - dmg > 0)
            target->components[0] -= dmg; // TODO: Maybe add defense calculation
        else
            die(target, i);
    }
}

void handleEnemies()
{
    for (int i = 0; i < world.size; i++)
    {

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
    }
}