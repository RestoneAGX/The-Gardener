#include <stdio.h>
#include "tools/Custom/Systems.h"

int main(){
    printf("--1-? %i\n", BitCheck(3, 1));
    printf("Base Num: 3\nClear: %i, Set: %i, Toggle: %i, %i\n", BitClear(3, 0), BitSet(3, 2), BitToggle(3, 1), BitToggle(3, 3));
    printf("%i\n", Renderable);
}