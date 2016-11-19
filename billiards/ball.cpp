#include <stdio.h>
#include <GLUT/GLUT.h>
#include <vector>
#include <cmath>
#include <math.h>
#include "BallAbstract.cpp"
#include "head/Vector.h"

class BallObject : public BallAbstract{
private:
    int m_id = 0;
    double m_BoxHeight = 15;
    double m_BoxWidth = 30;
    
public:
    double power = 0;
    GLfloat vector[3] = { 0.0,0.0,0.0 };
    GLfloat color[4] = {1.0,1.0,1.0,1.0};
    
    //玉の番号を付与
    void setId(int id){
        m_id = id;
    }
    
    //色を付与
    void setColor(float R,float G,float B,float A){
        color[0] = R;
        color[1] = G;
        color[2] = B;
        color[3] = A;
    }
    
    double pow(double p){
        p = p*p;
        return p;
    }
    
    void setPower(double d){
        power = d;
    }
    
    void getPower(double &p){
        p = power;
    }
    
    //方向を決めて値を入れる
    void setVectorPower(GLfloat uni[]){
        vector[0] = (float)(uni[0]*power);
        vector[1] = (float)(uni[1]*power);
        vector[2] = (float)(uni[2]*power);
    }
    
    void Physics(){
        power = power *0.99f;
        if(power < 0.1f){
            power = 0;
        }
        vector[0] =vector[0]*0.98;
        vector[1] =vector[1]*0.98;
        vector[2] =vector[2]*0.98;
    }
    
    void setPosition(){
        position->x = position->x+vector[0];
        position->y = position->y+vector[1];
        position->z = position->z+vector[2];
    }
    
    void setPositionPro(float x, float y, float z){
        vector[0] = x;
        vector[1] = y;
        vector[2] = z;
    }
    
    void getVec(GLfloat *p){
        *p = vector[0];
        ++p;
        *p = vector[1];
        ++p;
        *p = vector[2];
    }
    
    void setPosition(float x, float y, float z){

        position->x = x;
        position->y = y;
        position->z = z;
    }
    
    
    //壁に当たったとき反転
    void collisionDetectionBox(){
        
        //getPositionを消す
        GLfloat p_form2[] = { 0.0,0.0,0.0 };
        
        getForm(p_form2);
        
        
        
        //left
        if(position->x < 0.0 && position->z < m_BoxHeight){
            setPosition(0.1, position->y, position->z);
            setPositionPro(-vector[0], vector[1], vector[2]);
        }
        //down
        if(position->x < m_BoxWidth && position->z<0.0){
            setPosition(position->x, position->y, 0.1);
            setPositionPro(vector[0], vector[1], -vector[2]);
        }
        //right
        if(position->x > m_BoxWidth && position->z < m_BoxHeight){
            setPosition(29.9, position->y, position->z);
            setPositionPro(-vector[0], vector[1], vector[2]);
        }
        //up
        if(position->x < m_BoxWidth && position->z > m_BoxHeight){
            setPosition(position->x, position->y, 14.9);
            setPositionPro(vector[0], vector[1], -vector[2]);
        }
    }
    
};
