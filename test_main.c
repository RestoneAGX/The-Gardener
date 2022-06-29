#include <stdio.h>
#include "tests/world_tests.h"

int main(int argc, char *argv[])
{
    if (world_test())
    {
        printf("World Test failed\n");
        return -1;
    }
    return 0;
}