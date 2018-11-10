//
//  main.cpp
//  Proj2
//
//  Created by Eduardo Rubio on 10/11/18.
//  Main driver for the program 
//

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "structs.h"
#include "initializerFunctions.cpp"
#include "circles.h"
#include "tree.h"
#include "animation.cpp"
#include "MouseKeyb.cpp"
using namespace std;

int main(int argc, char * argv[]) {
    
    myglutInit(argc, argv);
    myInit();
    createTree();
    glutMouseFunc(mouse);
    glutSpecialFunc(specialKeyb);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
