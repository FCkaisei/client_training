#include <iostream>
#include <GLUT/GLUT.h>
#ifndef __CAMERASETTING_H_INCLUDED__
#define __CAMERASETTING_H_INCLUDED__
/*
 Camera
 */
class CameraSetting{
public:
    //どのカメラを利用するか選ぶ
    void createView(GLfloat gl[]);
    void createView(GLfloat p_pos[], float rsin, float rcos);
};


#endif