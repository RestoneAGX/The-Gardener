#include <stdlib.h>
#include <time.h>
#include <ECS.h>

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
    unsigned char moves = generate_range(4, 12);
    unsigned char x[12], y[12];
    unsigned char last_dir = 0;
    
    for (int i = 0; i < moves; i++){
        switch (generate_range(0, 3)){ // Generate a direction
            case 3:
            break;
            
            case 2:
            break;

            case 1:
            break;

            default:
            break;}
    } 
}