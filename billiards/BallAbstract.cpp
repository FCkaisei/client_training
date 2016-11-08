#include <iostream>
#include <GLUT/GLUT.h>
#include "objectAbstract.cpp"
#pragma once

class BallAbstract: public ObjectAbs{
    
    
public:
    
    virtual void setID(int i) = 0;
    
    virtual void setPower(double d) = 0;
    
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
    
    void getPosition(GLfloat *p){
        
        *p = positionX;
        ++p;
        *p = positionY;
        ++p;
        *p = positionZ;
    }
    
    void setPosition(float x, float y, float z){
        positionX = x;
        positionY = y;
        positionZ = z;
    }
    void Draw(void){
        glTranslatef(positionX,positionY,positionZ);
        glutSolidSphere(width,depth,height);
    }
    
protected:
    float positionX = 0;
    float positionY = 0;
    float positionZ = 0;
    float width = 0;
    float height = 0;
    float depth = 0;
};
