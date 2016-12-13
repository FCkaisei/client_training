#include <iostream>
#include <GLUT/GLUT.h>
#include "Vector.h"
#include "GameValue.h"
#include "../BallAbstract.cpp"
#ifndef __CAMERASETTING_H_INCLUDED__
#define __CAMERASETTING_H_INCLUDED__


class BallObject : public BallAbstract{
private:
    int m_id;
    double m_BoxHeight;
    double m_BoxWidth;
    
public:
    double power;
    GLfloat vector[3];
    GLfloat color[4];
    bool is_move;
    bool is_Existence;
    //玉の番号を付与
    void setId(int id);
    
    
    int getId();
    
    //色を付与
    void setColor(float R,float G,float B,float A)
    
    double pow(double p);
    
    void setPower(double d);
    
    void getPower(double &p);
    
    //方向を決めて値を入れる
    void setVectorPower(GLfloat uni[]);
    
    void Physics();
    
    void setPosition()
    
    GLfloat getPosition_x();
    
    GLfloat getPosition_y();
    
    GLfloat getPosition_z();
    
    void setPositionPro(float x, float y, float z);
    
    void getVec(GLfloat *p);
    GLfloat getVector_x();
    GLfloat getVector_z();
    
    void setPosition(float x, float y, float z);
    
    //壁に当たったとき反転
    void collisionDetectionBox();
    void inPocket();
    
    //穴に当たったときの挙動
    void collisionPockets();
}



#endif
