#include "../tools/ECS.h"
#include "../tools/Rendering.h"

#define MAX 100

int world_test(){
    printf("[World_Test Started]...\n");

    world_array *arr = &(world_array){};
    init_world(arr, MAX);

    if (arr->size != 0){
        printf("Initial Array size is ! [Error]\n");
        return -1;
    }

    if (arr->cap != MAX){
        printf("Array Capcity doesn't match up.");
        return -1;
    }

    for (int i = 0; i < MAX; i++)
        add_element(arr, entity_buffer, 3, 0,0);

    for (int i = 0; i < MAX; i++){
        // DEBUG
        // printf("Entity %d, indicator: %d, id: %d, sprite: %p, src: %p\n", i, arr->elements[i].indicator, arr->elements[i].id, arr->elements[i].sprite, arr->elements[i].src);
        
        if (arr->elements[i].indicator != entity_buffer[3].indicator){
            printf("entity %i's indicator doesn't not match the default\n", i);
            printf("entity: %d, Default: %d\n", arr->elements[i].indicator, entity_buffer[3].indicator);
            return -1;
        }

        if (arr->elements[i].id != entity_buffer[3].id){
            printf("entity %i's id doesn't not match the default\n", i);
            printf("entity: %d, Default: %d\n", arr->elements[i].id, entity_buffer[3].id);
            return -1;
        }

        if (arr->elements[i].sprite == NULL){
            printf("entity %i's sprite is NULL\n", i);
            return -1;
        }

        if (arr->elements[i].src == NULL){
            printf("entity %i's src is NULL\n", i);
            return -1;
        }

        if (arr->elements[i].components == NULL){
            printf("entity %i's components is NULL\n", i);
            return -1;
        }
    }

    for (int i = MAX-1; i > -1; i--){
        // DEBUG
        // printf("Entity %d, indicator: %d, id: %d, sprite: %p, src: %p\n", i, arr->elements[i].indicator, arr->elements[i].id, arr->elements[i].sprite, arr->elements[i].src);
        remove_element(arr, i);
    }

    if (arr->size != 0){
        printf("End Array size is !0 [Error]\n");
        return -1;
    }

    free_world(arr); // Add checking if you feel like it [Unlikely to cause bugs, so no need to test, right??????]

    printf("[World_Test Ended Sucessfully]\n");

    return 0;
}