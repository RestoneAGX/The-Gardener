#include <stdio.h>
#include "tests/world_tests.h"
#include "tests/combat_tests.h"

#define assert_err(condition, error_msg) \
    if (condition)                 \
    {                              \
        printf(error_msg);               \
        return -1;                 \
    }

int main(int argc, char *argv[])
{
    assert_err(world_test(), "World Test failed\n")
    assert_err(hitbox_test(), "Hitbox Test Failed\n"); // TODO: provide which part of the test failed through a return index for the test (like test 2 of hitbox test failed)
    return 0;
}
