#include <stdlib.h>
#include <time.h>

#define Max_Enemies 12

int instances = 0;
int current_stage = 0;

int random(){
    srand(time(0) * instances++);
    return rand();
}

int generate_range(int min, int max){
    srand(time(0) * instances++);
    return (rand() % (max - min + 1)) + min;
}

// if world size == 0; if ++current_stage == Boss_Room -> Start_boss; else -> generateRoom;

void generateRoom(world_array *world){
    for (int i = 0; i < generate_range(3, 16); i++){
        // int x = generate_range(0, W_WIDTH);
        // int y = generate_range(0, W_HEIGHT);
        // int enemy = generate_range(0, Max_Enemies);
        // add_element(world, eBuffer + enemy, x, y); // TODO: Make enemy buffer
    } 
}