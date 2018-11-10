//
//  circles.cpp
//  Proj2
//
//  Created by Eduardo Rubio on 10/11/18.
//  Class for the circle ( in this case, arc ) approximation
//

#include "circles.h"

/**
 * Generates an estimate of how many circle segments will be needed with a given radius
 */
int getNumCircleSegments(float r){
    return 10 * sqrtf(r);
}

/**
 * Creates an Arc to be used as the tree canopy
 */
void makeArc(float xPos, float yPos, float r, float start_angle, float arc_angle)
{
    //Circle approximations derived from online Physics forum (independent html site). User "SigeLord"
    //  suggested utilizing centripital acceleration and radial speed vectors of a circle to approximate
    //  points in a counterclockwise fashion
    
    int num_segments = getNumCircleSegments(r);
    float theta = arc_angle / float(num_segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
    
    float tangetial_factor = tanf(theta);
    float radial_factor = cosf(theta);
    
    float x = r * cosf(start_angle);//we now start at the start angle
    float y = r * sinf(start_angle);
    
    for(int iter = 0; iter < num_segments; iter++)
    {
        
        Point newPoint;
        newPoint.x = x + xPos;
        newPoint.y = y + yPos;
        TREE_POINTS.push_back( newPoint );
        
        float tx = -y;
        float ty = x;
        
        x += tx * tangetial_factor;
        y += ty * tangetial_factor;
        
        x *= radial_factor;
        y *= radial_factor;
    }
}
