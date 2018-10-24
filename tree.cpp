//
//  tree.cpp
//  Proj2
//
//  Created by Eduardo Rubio on 10/11/18.
//   Runs all the transformations on the tree as well as its redering 
//

#include "tree.h"

/**
 *Generates all the starting vertices of the tree by storing them in a Point vector
 */
void createTree( ){
    
    Point v0 = {200,450};
    Point v1 = {200,350};
    Point v2 = {510,375};
    Point vLastInner = {510,410};
    
    TREE_POINTS.push_back(v0); 
    TREE_POINTS.push_back(v1);
    TREE_POINTS.push_back(v2);
    makeArc(500, 400, 100, 4.25, 4);
    TREE_POINTS.push_back(vLastInner);

}

/**
 * Draws out the tree from given points in a Point vector 
 */
void drawTree( ){
    
    int xPlusOne;
    for ( int x = 0; x < TREE_POINTS.size(); x++ ){
        xPlusOne = (x+1)%TREE_POINTS.size();
        glBegin(GL_LINES);
        glVertex2d(TREE_POINTS[x].x, TREE_POINTS[x].y);
        glVertex2d(TREE_POINTS[xPlusOne].x, TREE_POINTS[xPlusOne].y);
        glEnd();
    }
}

/**
 * Draws out the tree from given points in a Point vector
 */
void drawTree( std::vector<Point> v ){
    
    int xPlusOne;
    for ( int x = 0; x < v.size(); x++ ){
        xPlusOne = (x+1)%v.size();
        glBegin(GL_LINES);
        glVertex2d(v[x].x, v[x].y);
        glVertex2d(v[xPlusOne].x, v[xPlusOne].y);
        glEnd();
    }
}

/**
 * Resets the tree to original position and stops all animations
 */
void resetTree( ){
    
    /**glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/
    TREE_POINTS.clear();
    TRIANGLES.clear();
    T_LINES.clear(); 
    IS_ROTATING = false;
    createTree();
    drawTree(); 
    
}

/**
 * Reflects the tree over its midpoint
 */
void reflectTree( ){
    
    for( int x = 0; x < TREE_POINTS.size(); x++ )
        TREE_POINTS[x].x = (TREE_POINTS[x].x * -1) + 800;
    
}

/**
 *Convert degrees to radians
 */
double degreesToRadians( double degrees ){
    return degrees * (M_PI / 180 );
}

/**
 * Rotates the individual point to its new location
 */
Point rotate( Point p, double theta ){
    
    double cos =  cosf( degreesToRadians(theta));
    double sin =  sinf( degreesToRadians(theta));
    
    p.x -= 400;
    p.y -= 400;
    
    double newX = cos*p.x - sin*p.y;
    double newY = sin*p.x + cos*p.y;
    
    p.x = newX + 400;
    p.y = newY + 400;
    
    return p;
    
}

/**
 * Begins the rotation for the entire tree
 */
void rotateTree( double theta ) {
    
    for( int x = 0; x < TREE_POINTS.size(); x++ )
        TREE_POINTS[ x ] = rotate(TREE_POINTS[ x ], theta);
    
}

/**
 * Scales an individual point. Int value will indicate an increase/decrease (positive int increases, negative decreases)
 */
Point scale( Point p, int Direction){
    
    if( Direction == 1){
        p.x = (p.x * 1.05) - 20.0;
        p.y = (p.y * 1.05) - 20.0;
    } else {
        p.x = (p.x *.95) + 20.0;
        p.y = (p.y *.95) + 20.0;
    }
    
    return p;
}

/**
 *Applies the scaled/translated transformation to the tree to be rendered onto the screen
 */
void scaleTree( int Direction ){
    
    for( int x = 0; x < TREE_POINTS.size(); x++ )
        TREE_POINTS[ x ] = scale(TREE_POINTS[x], Direction);
    
}



