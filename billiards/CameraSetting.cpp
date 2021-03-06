#include <iostream>
#include <GLUT/GLUT.h>
#include "head/CameraSetting.h"


/*
 Camera
 */
void CameraSetting::createView(GLfloat gl[]){
    gluLookAt(gl[0],gl[1],gl[2],
              20.0, 1.0, 10,
              0.0,3.0,0.0
              );
    
};
//p_positionとrsinが必要
void CameraSetting::createView(Vector position){
    float x = position.x;
    float z = position.z;
    gluLookAt(
              x+rsin, 3.0, z+rcos,
              x, 0.0, z,
              0.0, 1.0, 0.0
              );
}
