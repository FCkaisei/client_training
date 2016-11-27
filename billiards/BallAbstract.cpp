#include <iostream>
#include <GLUT/GLUT.h>
#include "objectAbstract.cpp"
#include "head/Vector.h"
#pragma once

class BallAbstract: public ObjectAbs{
    
    
public:
    Vector *position;
    float width = 0;
    float height = 0;
    float depth = 0;
    
    virtual void setPower(double d) = 0;
    
    virtual void setPosition(float x, float y, float z) = 0;
    void setForm(float w, float d, float h){
        width = w;
        depth = d;
        height = h;
    }
    
    void getForm(GLfloat *p){
        *p = width;
        ++p;
        *p = depth;
        ++p;
        *p = height;
    }
    
    void Draw(void){
        glTranslatef(position->x,position->y,position->z);
        glutSolidSphere(width,depth,height);
    }
    
    BallAbstract(){
         position = new Vector();
    }
};
