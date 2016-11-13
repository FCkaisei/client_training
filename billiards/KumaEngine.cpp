#include <GLUT/GLUT.h>
#include <math.h>
#pragma once

class KumaEngine{
public:
    static void UnitVector(GLfloat point1[],GLfloat point2[], GLfloat *p){
        GLfloat pp[] = { (float)(point1[0] - point2[0]), (float)(point1[1] - point2[1]), (float)(point1[2] - point2[2]) };
        float a = sqrt(pp[0]*pp[0]+pp[1]*pp[1]+pp[2]*pp[2]);
        GLfloat pp2[] = { (float)(pp[0]/a),pp[1]/a,(float)(pp[2]/a)};
        *p = pp2[0];
        ++p;
        *p = pp2[1];
        ++p;
        *p = pp2[2];

    }

};
