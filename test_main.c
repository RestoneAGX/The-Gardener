#include <stdio.h>
#include "tests/world_tests.h"

#define assert_err(condition, error_msg) \
    if (condition)                 \
    {                              \
        printf(error_msg);               \
        return -1;                 \
    }

int main(int argc, char *argv[])
{
    assert_err(world_test(), "World Test failed\n")
    return 0;
}