//
//  MouseKeyb.cpp
//  Proj2
//
//  Assigns functions to all keyboard and mouse interaction
//

#include <stdio.h>

/**
 * Checks to see if mouse is within the viewport.
 */
bool inViewport( int x, int y ) {
    
    if( VIEWPORT_MIN < x && x < VIEWPORT_MAX
       && VIEWPORT_MIN < y && y < VIEWPORT_MAX)
        return true;
    
    return false;
}

/**
 * Mouse interaction definition
 */
void mouse( int button, int state, int x, int y ){
    if( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN ){
        if( inViewport(x, y) )
            scaleTree(-1);
        else{
            SPIN--;
            rotationAnimation();
        }
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ){
        
        if( inViewport(x, y) )
            scaleTree( 1 );
        else{
            SPIN++;
            rotationAnimation();
        }
    }
    
    glutPostRedisplay();
}

/**
 * Keyboard interaction definition
 */
void keyboard( unsigned char key, int x, int y ){
    
    
    if( key == 'q' || key == 'Q' ) exit(0); // Quit
    if( key == 'f' || key == 'F' ) { } // Fill through tesselation
    if( key == 't' || key == 'T' ) { triFill(); } // Show triangles
    if( key == 'l' || key == 'L' ) { } // Show wireframe
    if( key == 'r' || key == 'R' ) reflectTree(); //reflect tree
    if( key == 's' || key == 'S' ) stopAnimation(); //stops animation
    if( key == 'i' || key == 'I' ) resetTree(); // Stop animation and return tree to original position
    if( key == 'f' || key == 'F' ) {
        IS_FILLED = true; 
        //triFill();
    }
    if( key == 'x' || key == 'X' ) glutSwapBuffers(); //Swap buffer by hand

    
    glutPostRedisplay(); 
}
