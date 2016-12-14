#include <stdio.h>
#include <GLUT/GLUT.h>
#include <vector>
#include <cmath>
#include "head/LightObject.h"

void LightObject::createLight(){
    GLfloat lightPos[] = { 20.0, 30.0, 10.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}
