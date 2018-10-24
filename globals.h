//
//  globals.cpp
//  Proj2
//
//  Created by Eduardo Rubio on 10/11/18.
//  Global variables for the entire program

#include <stdio.h>
#include <vector>

int COLORS_DEFINED;

/**
 * Window specifications
 */
const int WINDOW_POSITION_X = 100;
const int WINDOW_POSITION_Y = 100;
const int WINDOW_MAX_X = 800;
const int WINDOW_MAX_Y = 800;

const float WORLD_COORDINATES_MIN_X = 0.0;
const float WORLD_COORDINATES_MAX_X = 800.0;
const float WORLD_COORDINATES_MIN_Y = 0.0;
const float WORLD_COORDINATES_MAX_Y = 800;

const float VIEWPORT_MIN = 100;
const float VIEWPORT_MAX = 700; 

int SPIN = 0; 

std::vector<Point> TREE_POINTS; //Stores tree points
std::vector<Triangle> TRIANGLES;
std::vector<LineSeg> T_LINES; 
/**
 * Safety for the animations to continue/stop 
 */
bool IS_ROTATING = false;
bool IS_FILLED = false; 


