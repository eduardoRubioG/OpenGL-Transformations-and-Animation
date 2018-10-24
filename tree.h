//
//  tree.hpp
//  Proj2
//
//  Runs all the transformations on the tree as well as its redering 
//

#ifndef tree_hpp
#define tree_hpp
#include <stdio.h>
#include "circles.h"

class Tree{
  
public:
    void CreateTree( );
    void drawTree( );
    void scaleTree( int );
    void rotateTree( double );
    void reflectTree( ); 
    
private:
    Point scale( Point, int );
    Point rotate( Point, double );
    double degreesToRadians( double );
};

#include "tree.cpp"
#endif /* tree_hpp */
