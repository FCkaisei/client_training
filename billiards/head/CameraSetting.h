#include <iostream>
#include <GLUT/GLUT.h>
#include "Vector.h"
#include "GameValue.h"
#ifndef __CAMERASETTING_H_INCLUDED__
#define __CAMERASETTING_H_INCLUDED__
/*
 Camera
 */

class CameraSetting{
public:
    //どのカメラを利用するか選ぶ
    void createView(GLfloat gl[]);
    void createView(Vector position);
};


#endif
