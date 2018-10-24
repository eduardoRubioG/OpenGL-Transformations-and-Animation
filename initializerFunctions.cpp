//Linux Headers
/*
 #include <GL/glut.h>
 */
//Mac headers
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
//
#include <stdio.h>
#include "globals.h"
#include <math.h>
#include "clipping.cpp"
#include "tree.h"

void myglutInit( int argc, char** argv ){
    glutInit( &argc, argv );
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_MAX_X, WINDOW_MAX_Y);
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
    glutCreateWindow("The Magic Tree");
}

void myInit(void){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);
    
    COLORS_DEFINED = 0;
    
    glViewport(0, 0, 100, 100);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(WORLD_COORDINATES_MIN_X, WORLD_COORDINATES_MAX_X, WORLD_COORDINATES_MIN_Y, WORLD_COORDINATES_MAX_Y);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /*Define the viewport*/
    glColor3f(1.0, 1.0, 1.0); //
    glRecti(VIEWPORT_MIN, VIEWPORT_MIN, VIEWPORT_MAX, VIEWPORT_MAX);
    
    /* Draw the tree */ 
    glColor3f(1.0, 0.0, 1.0);
    drawTree( shClip() ); //Clips before rendering 
    glutSwapBuffers();
}
