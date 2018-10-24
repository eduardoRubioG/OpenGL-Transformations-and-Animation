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
    if( getAngle(untouchedPoints[ firstPointIndex ],
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

//Will we need this???
void newLineSeg( Point one, Point two ){
    LineSeg newLine;
    newLine.first = one;
    newLine.second = two;
    T_LINES.push_back(newLine);
}


/**
 * Final steps to finishing tesselation. Called when there are 4 points left in polygon
 */
void fourTipFinish( std::vector<Point> v ) {
    
    //Finds midpoint of proposed line
    double mp13[2];
    midpoint( v[1], v[3], mp13);
    
    //Checks to make sure the midpoint is within the constraints of the polygon
    if( (mp13[0] > v[0].x && mp13[0] < v[2].x
         && mp13[1] < v[3].y && mp13[1] > v[1].y)
       ||
       (mp13[0] > v[1].x && mp13[0] < v[3].x
        && mp13[1] < v[0].y && mp13[1] > v[2].y)){
           
           drawLine(v[1], v[3]);
           newTriangle( 0,1,3,v );
           newTriangle( 1,2,3,v );
           
       } else {
           drawLine(v[0], v[2]);
           newTriangle( 0,1,2,v );
           newTriangle( 0,2,3,v );
       }
}

/**
 * Tesselate the user drawn polygon using ear-clipping method
 */
void tesselate( ) {
    
    int iterations = 0;
    //Will be used for to maintain which points have not been clipped
    std::vector<Point> untouchedPoints = TREE_POINTS;
    
    for( int x = 0; x < untouchedPoints.size(); x++ ){
        
        //printPolPointVectors(untouchedPoints);
        int xPlusOne = (x+1)%untouchedPoints.size();
        int xPlusTwo = (x+2)%untouchedPoints.size();
        
        //In the special case that there is a four point polygon, simply 'cut' it in half
        if( untouchedPoints.size() == 4 ){
            fourTipFinish(untouchedPoints);
            return;
        }
        
        if( untouchedPoints.size() == 3 )
        {
            newTriangle(0, 1, 2, untouchedPoints);
            //newLineSeg(untouchedPoints[0], untouchedPoints[2]);
            return;
        }
        
        if( !finishedPolygonIntersect( x , xPlusTwo , untouchedPoints) ) {// point x and x+2 do not have an intersection
            //newLineSeg( untouchedPoints[x], untouchedPoints[xPlusTwo] );
            iterations++;
            printLine(untouchedPoints[x], untouchedPoints[xPlusTwo]);
            drawLine(untouchedPoints[x], untouchedPoints[xPlusTwo]); 
            newTriangle(x, xPlusOne, xPlusTwo, untouchedPoints);
            untouchedPoints.erase( untouchedPoints.begin() + xPlusOne );     //Remove the middle point of the triangle
            x = 0;  //Return x to 0 to continue ear-clipping algorithm
        }
    }//end of for-loop
}

/**
 *
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
    //glutSwapBuffers();
}

void drawWireFrame( ) {
    
    for( int x = 0; x < T_LINES.size(); x++ ){
        
        glBegin(GL_LINES);
        glVertex2d(T_LINES[x].first.x, T_LINES[x].first.x);
        glVertex2d(T_LINES[x].second.x, T_LINES[x].second.y);
        glEnd();
        //glutSwapBuffers();
    }
}

