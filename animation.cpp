//
//  animation.cpp
//  Proj2
//
//  Created by Eduardo Rubio on 10/12/18.
//  Runs the animation functions for the magic tree 
//

#include <stdio.h>

/**
 * Function that endlessly runs the animation until global bool, IS_ROTATING, is false
 */
void timer( int ) {
    
    if( !IS_ROTATING ){ //If the user stops the animation, this function is stopped
        return;
    } else {//Otherwise, continued animation 
        
        rotateTree( SPIN );
        
        glutPostRedisplay();
        glutTimerFunc(1000/60, timer, 0);
        
    }
}

/**
 * Stops animation of the tree
 */
void stopAnimation( ){
    IS_ROTATING = false;
    SPIN = 0; 
}

/**
 * Initiate the call to the time iterated function
 */
void rotationAnimation( ){
    IS_ROTATING = true;
    glutTimerFunc(0, timer, 0);
}
