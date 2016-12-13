#include "head/Label2D.h"

void Label2D::display2D(std::string str, float x, float y){
    glRasterPos2f(x, y);
    int size = (int)str.size();
    for(int i = 0; i < size; ++i){
        char ic = str[i];
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ic);
    }
}

void Label2D::display2D(std::string str, float x, float y,float z){
    glRasterPos3d(x, y, z);
    int size = (int)str.size();
    for(int i = 0; i < size; ++i){
        char ic = str[i];
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ic);
    }
}
