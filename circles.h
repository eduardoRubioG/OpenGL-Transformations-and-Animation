//
//  circles.hpp
//  Proj2
//
//  Created by Eduardo Rubio on 10/11/18.
//  Class for the circle ( in this case, arc ) approximation
//

#ifndef circles_hpp
#define circles_hpp

#include <stdio.h>

class Circle{
  
public:    
    void DrawArc(float cx, float cy, float r, float start_angle, float arc_angle);
    
private:
    int GetNumCircleSegments(float r); 
    
};

#include "circles.cpp"
#endif /* circles_hpp */
