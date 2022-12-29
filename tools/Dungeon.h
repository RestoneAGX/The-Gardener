#include "ECS.h"
#include <time.h>
#include <stdlib.h>

#define Max_Enemies 5

int instances = 0;
int current_stage = 0;

typedef struct room{
    int door: 4;
    int enemy_length;
}room;

int generate_random(){
    srand(time(0) * instances++);
    return (rand());
}

int generate_range(int min, int max){
    srand(time(0) * instances++);
    return (rand() % (max - min + 1)) + min;
}

// if world size == 0; if ++current_stage == Boss_Room -> Start_boss; else -> generateRoom;
void generateRoom(world_array *world){
    unsigned char moves = generate_range(4, 12);
    room rooms[moves];
    
    for (int i = 0; i < moves; i++){
        rooms[i].door = generate_range(0, 3);
        rooms[i].enemy_length = generate_range(3, 12);
    }
}
