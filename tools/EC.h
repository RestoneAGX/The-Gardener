#include<stdlib.h>
#define __OUT_OF_BOUNDS -2;

typedef struct{
    unsigned int indicator : 4;
    unsigned char id;
    unsigned char *components;
    float x, y; //Make these float 16s if possible
} entity;

typedef struct{
    int cap;
    int size;
    entity *elements;
} world_array;

void init_world(world_array *arr, size_t length){
    arr->size = 0;
    arr->cap = length;
    arr->elements = (entity *) calloc(length, sizeof(*arr->elements));
    if (arr->elements == NULL) return; //Return some sort of error indicating this
}

void expand_world(world_array *arr, size_t add_size){ //Watch this function for memory bugs [weird outputs]
    arr->elements = (entity *) realloc(arr->elements, (arr->cap + add_size) * sizeof(*arr->elements));
    if (arr->elements != NULL) arr->cap += add_size;
}

void add_element(world_array *arr, entity newValue){
    if (arr->size < arr->cap){
        *(arr->elements + arr->size) = newValue;
        arr->size++;
    }else expand_world(arr, arr->size + 1);
}

int remove_element(world_array *arr, int index){
    if (index < 0 || index > arr->size) return __OUT_OF_BOUNDS;
    arr->elements[index] = arr->elements[arr->size-1];
    arr->elements[arr->size-1] = (entity) {};
    arr->size -= 1;
    //Shrink if neccassary
    return 0;
}

void shrink_world(world_array *arr, size_t sub_size){
    arr->elements = (entity *) realloc(arr->elements, (arr->cap - sub_size) * sizeof(*arr->elements));
    arr->cap -= sub_size;

    if (arr->size == arr->cap) arr->size--;
}


void init_entity(entity *e){
    if (e->id == 0) e->components = (unsigned char*) malloc(10); //Allocate memory according to ID
}