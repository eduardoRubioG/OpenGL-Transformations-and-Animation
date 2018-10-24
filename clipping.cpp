//
//  clipping.cpp
//  Proj2
//
//  Created by Eduardo Rubio on 10/15/18.
//  Handles the clipping of polygons exiting the viewport

#include <stdio.h>
using namespace std;

Point cwBL = {VIEWPORT_MIN, VIEWPORT_MIN}; //Clip window bottom left (100,100)
Point cwBR = {VIEWPORT_MAX, VIEWPORT_MIN};//Clip window bottom right (700,100)
Point cwTL = {VIEWPORT_MIN, VIEWPORT_MAX};//Clip window top left     (100,700)
Point cwTR = {VIEWPORT_MAX, VIEWPORT_MAX};//Clip window top right    (700,700)
//std::vector<Point> clippers = {cwBL, cwBR, cwTR, cwTL}; //Viewport is the clipping point
std::vector<Point> clippers = {cwTL, cwTR, cwBR, cwBL};

/**
 * Displays point p on console for debugging purposes
 */
void printPoint( Point p ){
    cout << "(" << p.x << ", " << p.y << ")";
}

/**
 * Flips designated vector but maintains starting vertex. Will be used in case of user-drawn polygon being clockwise
 */
vector<Point> flipPoints( vector<Point> const originalVec ){
    
    vector<Point> newVec;
    
    newVec.push_back( originalVec[0] );
    for( int pos = (int) originalVec.size(); 1 < pos; pos-- ) {
        newVec.push_back( originalVec[ pos-1 ] );
    }
    
    return newVec;
}

/**
 *Finds the x intersection point
 */
float xIntersect( Point p1, Point p2, Point w1, Point w2){
    
    //Equation derived from the parametric line segment intersection equation
    float top = ((p1.x*p2.y - p1.y*p2.x)
                *(w1.x-w2.x)-(p1.x-p2.x)
                 *(w1.x*w2.y - w1.y*w2.x));
    
    float bottom = ((p1.x-p2.x) * (w1.y-w2.y)
                    -(p1.y-p2.y)*(w1.x-w2.x));
    
    return top/bottom;
}

/**
 *Finds the y intersection point
 */
float yIntersect( Point p1, Point p2, Point w1, Point w2 ){
    
    //Equation derived from the parametric line segment intersection equation
    float top = ((p1.x*p2.y - p1.y*p2.x)
                 * (w1.y-w2.y) - (p1.y - p2.y)
                 *(w1.x*w2.y-w1.y*w2.x));
    
    float bottom = ((p1.x-p2.x)*(w1.y-w2.y)
                    -(p1.y-p2.y)*(w1.x-w2.x));
    
    return top/bottom;
}

/**
 *Prints a vector of points
 */
void printPV( std::vector<Point> v){
    for( int x = 0; x < v.size(); x++ ){
        std::cout << "(" << v[x].x << ", " << v[x].y << ") " << std::endl;
    }
}

/**
 * SH-Algorithm helper method
 */
void clip( Point one, Point two, std::vector<Point> &tPoint ){

    std::vector<Point> newPoints;
    
    for( int pos = 0; pos < tPoint.size(); pos++ ){
     
        int nextPos = (pos+1) % tPoint.size();
        Point i = {tPoint[pos].x, tPoint[pos].y};
        Point k = {tPoint[nextPos].x, tPoint[nextPos].y};

        float iValue = (( two.x - one.x )*( i.y - one.y)
                        - (two.y - one.y)*(i.x - one.y));
        float kValue = ((two.x - one.x)*(k.y - one.y)
                        -(two.y -one.y)*(k.x-one.x));

        //Case 1: Both points are inside
        if( iValue < 0 && kValue < 0){
            //Only second point is added
            Point np = k;
            newPoints.push_back( np );
        }
        //Case 2: Only first point is on the outside
        else if( iValue  >= 0 && kValue < 0 ) {
            //Point of intersection with edge
            //and the second point is added
            Point newP;
            newP.x = xIntersect(one, two, i, k);
            newP.y = yIntersect(one, two, i, k);
            newPoints.push_back( newP );
            newPoints.push_back( k );
        }
        //Case 3: When only the second point is on the outside
        else if( iValue < 0 && kValue >= 0 ){
            //Only point of intersection with edge is added
            Point newP;
            newP.x = xIntersect(one, two, i, k);
            newP.y = yIntersect(one, two, i, k);
            newPoints.push_back( newP );
        }
        //Case 4: When both points are outside
        else { /* No points are added */ }
        
    }
    //Resize the vector
    tPoint.resize( newPoints.size() );
    newPoints = flipPoints(newPoints);
    for( int x = 0; x < newPoints.size(); x++ )
        tPoint[ x ] = newPoints[ x ];
    
}

/**
 * Runs the SH algorithm
 */
std::vector<Point>  shClip( ){
    
    std::vector<Point> tPoint = TREE_POINTS;
    for( int pos = 0; pos < 4; pos++ ){
        
        int nextPos = (pos+1)%4;
        clip( clippers[ pos ], clippers[ nextPos ], tPoint);
        
    }
    return tPoint; 

}


