#include "../tools/ECS.h"
#include "../tools/Rendering.h"
#include <stdio.h>
#include <assert.h>

#define MAX 100

int world_test(){
    printf("[World_Test Started]...\n");

    world_array *arr = &(world_array){};
    init_world(arr, 100);

    assert(arr->size == 0); // We assert that the size should start at 0, since no elements have been travesed

    assert(arr->cap == MAX); // We assert that the cap should be == to MAX elements

    for (int i = 0; i < MAX; i++)
        add_element(arr, entity_buffer + 3, 3.0, 3.0);

    for (int i = 0; i < MAX; i++){
        // DEBUG
        // printf("Entity %d, indicator: %d, id: %d, sprite: %p, src: %p\n", i, arr->elements[i].indicator, arr->elements[i].id, arr->elements[i].sprite, arr->elements[i].src);

        // Verify that the elements in the structs match
        assert(arr->elements[i].indicator == entity_buffer[3].indicator);

        assert(arr->elements[i].id == entity_buffer[3].id);

        assert(arr->elements[i].sprite->w == entity_buffer[3].sprite->w);

        assert(arr->elements[i].sprite->h == entity_buffer[3].sprite->h);

        assert(arr->elements[i].sprite->x == 3.0);

        assert(arr->elements[i].sprite->y == 3.0);

        assert(arr->elements[i].components != NULL);

        assert(arr->elements[i].src != NULL);

        assert(arr->elements[i].src == entity_buffer[3].src);
    }

    for (int i = MAX-1; i > -1; i--){
        // DEBUG
        // printf("Entity %d, indicator: %d, id: %d, sprite: %p, src: %p\n", i, arr->elements[i].indicator, arr->elements[i].id, arr->elements[i].sprite, arr->elements[i].src);
        remove_element(arr, i);
    }

    assert(arr->size == 0);

    free_world(arr); // Add checking if you feel like it [Unlikely to cause bugs, so no need to test, right??????]

    printf("[World_Test Ended Sucessfully]\n");

    return 0;
}
