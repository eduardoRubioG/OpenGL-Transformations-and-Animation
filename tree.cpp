//
//  tree.cpp
//  Proj2
//
//  Created by Eduardo Rubio on 10/11/18.
//   Runs all the transformations on the tree as well as its rendering
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
    int treeSize = TREE_POINTS.size();
    for ( int x = 0; x < treeSize; x++ ){
        xPlusOne = (x+1)%treeSize;
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
    int vSize = v.size();
    for ( int x = 0; x < vSize; x++ ){
        xPlusOne = (x+1)%vSize;
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
    
    TREE_POINTS.clear();
    TRIANGLES.clear();
    IS_TESSELATED = false;
    IS_WIREFRAME = false;
    IS_ROTATING = false;
    SPIN = 0; 
    createTree();
    drawTree(); 
    
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
    
    /* Include the ROT_POINT here for the translations*/
    p.x -= CENTER_POINT.x;
    p.y -= CENTER_POINT.y;
    
    double newX = cos*p.x - sin*p.y;
    double newY = sin*p.x + cos*p.y;
    
    p.x = newX + CENTER_POINT.x;
    p.y = newY + CENTER_POINT.y;
    
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
 *Reflect the tree
 */
void reflectTree( ){
     for( int i = 0; i < TREE_POINTS.size(); i++ ){
         TREE_POINTS[i].x *= -1;
         TREE_POINTS[i].x += CENTER_POINT.x * 2;
     }
    
    if( IS_REFLECTED )
        IS_REFLECTED = false;
    else
        IS_REFLECTED = true; 
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

/**
 * Moves tree around the XY-plane
 */
void moveTree( int xTranslate, int yTranslate){
    
    int treeSize = TREE_POINTS.size();
    CENTER_POINT.x += xTranslate;
    CENTER_POINT.y += yTranslate; 
    for( int i = 0; i < treeSize; i++ ){
        TREE_POINTS[i].x = TREE_POINTS[i].x + xTranslate;
        TREE_POINTS[i].y = TREE_POINTS[i].y + yTranslate;
    }
    
}



