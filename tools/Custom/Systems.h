#include "EC.h"

#define BitCheck(v,n) (v & (1 << n))
#define BitToggle(v,n) (v ^ (1 << n))
#define BitClear(v,n) (v & ~(1 << n))
#define BitSet(v,n) (v | (1 << n))

// 0 = false; 1 = true; Off by default
#define Renderable 0x1
#define item 0x2 //If active, it means that the attributes read afterwards should be 
// #define dynamic 0x4

enum sprites {Player};
