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
        if( !inViewport(x, y) )
            scaleTree(-1);
        else{
            SPIN--;
            rotationAnimation();
        }
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ){
        
        if( !inViewport(x, y) )
            scaleTree( 1 );
        else{
            SPIN++;
            rotationAnimation();
        }
    }
    glutPostRedisplay();
}

/**
 * Keyboard interaction for non-ASCII keys
 */
void specialKeyb( int key, int x, int y ){
    if( key == GLUT_KEY_RIGHT )    moveTree(5, 0);
    if( key == GLUT_KEY_LEFT)      moveTree(-5, 0);
    if( key == GLUT_KEY_UP)        moveTree(0, 5);
    if( key == GLUT_KEY_DOWN)      moveTree(0, -5);
    glutPostRedisplay();
}

/**
 * Keyboard interaction definition
 */
void keyboard( unsigned char key, int x, int y ){
    
    if( key == 'q' || key == 'Q' ) exit(0); // Quit
    if( key == 'f' || key == 'F' ) { IS_TESSELATED = true; IS_WIREFRAME = false; } // Fill in the tree
    if( key == 't' || key == 'T' ) { IS_WIREFRAME = true; IS_TESSELATED = false; } // Show wireframe
    if( key == 'l' || key == 'L' ) { IS_WIREFRAME = false; IS_TESSELATED = false; } //Show the bare tree
    if( key == 'r' || key == 'R' )  reflectTree();//reflectTree(); //reflect tree
    if( key == 's' || key == 'S' ) stopAnimation(); //stops animation
    if( key == 'i' || key == 'I' ) resetTree(); // Stop animation and return tree to original position
    glutPostRedisplay(); 
}
