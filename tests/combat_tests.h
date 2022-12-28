#include "../tools/Systems.h"
#include <stdio.h>
#include <assert.h>
#define make_pose(_x, _y, _w, _h) ( (SDL_FRect) {.x = _x, .y = _y, .w = _w, .h = _h} )

#define ref_point 0
#define range 5
#define HIT_POINTS 10
float x_vals[HIT_POINTS] = {-3, 5, 11, 15, 12, 14, -15, 19, 10, 2 };
float y_vals[HIT_POINTS] =  {0, 0, -10, 0,  0,  0,  0,  0,   0,  3 };
//int expected_returns[HIT_POINTS] =  {0, 1, 0,  0,  0,  0,  0,  0,   0,  1 };

int expected_returns[HIT_POINTS] = {};
//TODO: REDO this entire function
int hitbox_test(){
    printf("[Hitbox Test started...]\n");
    
    entity point = (entity) { .sprite = make_pose(0,0,0,0), .components = {255}};

    for (int i = 0; i < HIT_POINTS; i++){
        point.sprite.x = x_vals[i];
        point.sprite.y = y_vals[i];
        assert( hitbox(&point, 0, 0, ref_point, range) == expected_returns[i]);
    }
    
    printf("[HitBox Test Complete]\n");
    return 0;
}
