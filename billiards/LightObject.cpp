#include <stdio.h>
#include <GLUT/GLUT.h>
#include <vector>
#include <cmath>
#include "head/LightObject.h"

void LightObject::createLight(){
        GLfloat light0pos[] = { 0.0, 3.0, 5.0, 1.0 };
        glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
}
