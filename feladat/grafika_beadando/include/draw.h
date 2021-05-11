#ifndef INCLUDE_DRAW_H_
#define INCLUDE_DRAW_H_

#include "model.h"

#ifndef GL_EXT_texture_edge_clamp
#define GL_CLAMP_TO_EDGE                 0x812F
#endif

// Draw the content.
void draw_content(World* world);

// Draws the ground.
void draw_ground(Map map);

// Draws the room.
void draw_walls(Map map);

// Draws the finish line.
void draw_finish(Map map);

// Draws the help menu
void draw_help(int texture);

// Draws the boxes
void draw_boxes(int moveX, int moveZ,int degree);

// Draws the cars
void draw_cars(int moveX, int moveZ,int degree);

#endif /* INCLUDE_DRAW_H_ */
