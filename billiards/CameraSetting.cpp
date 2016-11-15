#include <iostream>
#include <GLUT/GLUT.h>
#include "head/CameraSetting.h"
/*
 Camera
 */
    //どのカメラを利用するか選ぶ
void CameraSetting::createView(GLfloat gl[]){
    gluLookAt(gl[0],gl[1],gl[2],
              15.0, 1.0, 7.5,
              0.0,3.0,0.0
              );
    
};
//p_positionとrsinが必要
void CameraSetting::createView(GLfloat p_position[], float rsin, float rcos){
    gluLookAt(
              (float)p_position[0]+rsin, 3.0, (float)p_position[2]+rcos,
              (float)p_position[0], 0.0, (float)p_position[2],
              0.0, 1.0, 0.0);
}