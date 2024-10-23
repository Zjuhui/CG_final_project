#ifndef DEFINE_LIST_H
#define DEFINE_LIST_H

// Floor and world position limitations


#define FLOOR_SIZE 300
#define FLOOR_MAX_POSITION 50
#define FLOOR_UNIT (2.0*FLOOR_MAX_POSITION/FLOOR_SIZE)
#define FLOOR_COLOR 0.6
#define GET_POS(x,y) ((x)*(FLOOR_SIZE+1)+(y))
#define OUT_RADIUS 6
#define IN_RADIUS 2
#define FLOOR_ELEMENT_COUNT 9

#define LIGHT_POS 2*FLOOR_MAX_POSITION,100.0f,0.5*FLOOR_MAX_POSITION

// Shadow
#define SHADOW_WIDTH 2048
#define SHADOW_HEIGHT 2048
#define SHADOW_LIGHT_POS FLOOR_MAX_POSITION-5,30.0f,0
#define SHADOW_WATCH_POS 0,0,0

// settings
// Window
#define SCR_WIDTH 800
#define SCR_HEIGHT 600


#endif 
