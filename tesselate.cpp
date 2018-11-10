//
//  tesselate.cpp
//  Proj2
//
//  Created by Eduardo Rubio on 10/12/18.
//  Handles all tesselation functions
//

#include <stdio.h>
#include "TesselateHelpers.h"

/**
 * Intersection checker specifically for use during tesselation
 */
bool finishedPolygonIntersect( int firstPointIndex, int secondPointIndex, std::vector<Point> untouchedPoints ) {
    
    //1.    Check if point a, middle point, and point b are counterclockwise
    //      If counterclockwise proceed to next step. If not, report intersection
    if( orientation( untouchedPoints[ firstPointIndex ],
                    untouchedPoints[ firstPointIndex + 1 ],
                    untouchedPoints[ secondPointIndex ]) != 2 )
        return true;
    
    //2. Check to see if proposed line will go outside of the polygon
    if( getAngle( untouchedPoints[ firstPointIndex ],
                 untouchedPoints[ firstPointIndex + 1 ],
                 untouchedPoints[ secondPointIndex ]) > 180)
        return true;
    
    //3. Check for intersections
    for( int x = 0; x < untouchedPoints.size(); x++ ){
        
        int xPlusOne = (x+1)%untouchedPoints.size();
        
        //Check if line segments in question are adjacent
        if( !isAdjacent(x, xPlusOne, firstPointIndex, secondPointIndex))
            
            //Lines are not adjacent, so check for intersection
            if (  doesIntersect(  untouchedPoints[ x ],
                                untouchedPoints[ xPlusOne ],
                                untouchedPoints[ firstPointIndex ],
                                untouchedPoints[ secondPointIndex ]) )
                return true;
        
    }
    return false;
}

void printLine( Point a, Point b){
    cout << "<" << a.x << ", " << a.y << "> ---> <" << b.x << ", " << b.y <<"> " << endl;
}

/**
 * Add new triangle
 */
void newTriangle( int indexP, int indexQ, int indexR, std::vector<Point> const vector ) {
    Triangle t;
    t.first = vector[ indexP ];
    t.second = vector[ indexQ ];
    t.third = vector[ indexR ];
    TRIANGLES.push_back( t );
}

/**
 * Tesselate the user drawn polygon using ear-clipping method
 */
void tesselate(  ) {
    
    //Will be used for to maintain which points have not been clipped
    std::vector<Point> untouchedPoints;
    if( IS_REFLECTED )
        untouchedPoints = flipPoints(POST_CLIP_TREE);
    else
        untouchedPoints = POST_CLIP_TREE;
        
    for( int x = 0; x < untouchedPoints.size(); x++ ){
        
        //printPolPointVectors(untouchedPoints);
        int xPlusOne = (x+1)%untouchedPoints.size();
        int xPlusTwo = (x+2)%untouchedPoints.size();
        
        if( untouchedPoints.size() == 3 )
        {
            newTriangle(0, 1, 2, untouchedPoints);
            return;
        }
        
        if( !finishedPolygonIntersect( x , xPlusTwo , untouchedPoints) ) {// point x and x+2 do not have an intersection
            drawLine(untouchedPoints[x], untouchedPoints[xPlusTwo]);
            newTriangle(x, xPlusOne, xPlusTwo, untouchedPoints);
            untouchedPoints.erase( untouchedPoints.begin() + xPlusOne );     //Remove the middle point of the triangle
            x = 0;  //Return x to 0 to continue ear-clipping algorithm
        }
    }//end of for-loop
}

/**
 * Fills out all the triangles after tesselation
 */
void triFill( ){
    
    tesselate();
    for( int x = 0; x < TRIANGLES.size(); x++ ){
        
        glBegin(GL_TRIANGLES);
        glVertex2d(TRIANGLES[x].first.x, TRIANGLES[x].first.y);
        glVertex2d(TRIANGLES[x].second.x, TRIANGLES[x].second.y);
        glVertex2d(TRIANGLES[x].third.x, TRIANGLES[x].third.y);
        glEnd();
        
    }
}

/**
 * Decides whether or not to tesselate depending on user interactions. Called from the display function
 */
void toTesselate( ){
    if( !TRIANGLES.empty() )
        TRIANGLES.clear();
    
    if( IS_TESSELATED ){
        tesselate();
        triFill();
    }
    else if( IS_WIREFRAME ){
        tesselate();
    }
}


