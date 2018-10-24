//
//  TesselateHelpers.hpp
//  Proj2
//
//  Created by Eduardo Rubio on 10/12/18.
//  Copyright © 2018 Eduardo Rubio. All rights reserved.
//

#ifndef TesselateHelpers_hpp
#define TesselateHelpers_hpp

#include <stdio.h>

template <class Object>
class gMath {
    
public:
    double dotProd( std::vector<Object> const& a, std::vector<Object> const& b );
    void crossProd( std::vector<Object> const& a, std::vector<Object> const& b,
                   std::vector<Object> const& resultingVector );
    bool doesIntersect( Point const p1, Point const q1, /*Algorithm from GeeksforGeeks*/
                       Point const p2, Point const q2  );
    int orientation( Point const p,
                     Point const q,
                     Point const r );
    double getAngle( Point const p, Point const q, Point const r );
    bool doesExitPolygon( Object const p[], Object const q[], Object const r[] );
    bool isAdjacent( Object x, Object xPlusOne, Object firstPointIndex, Object secondPointIndex);
    void  midpoint( Point const p, Point const q, double midpointArray[]);
    void drawLine( Point const p, Point const q );
    
private:
    bool onSegment( Point const p,
                   Point const q,
                   Point const r ); /*For doesIntersect function*/
};

#include "TesselateHelpers.cpp"
#endif /* TesselateHelpers_hpp */
