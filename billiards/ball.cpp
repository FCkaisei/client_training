#include <stdio.h>
#include <GLUT/GLUT.h>
#include <vector>
#include <cmath>
#include <math.h>
#include "head/GameValue.h"
#include "BallAbstract.cpp"
#include "head/Vector.h"

class BallObject : public BallAbstract{
private:
    int m_id = 0;
    double m_BoxHeight = 20;
    double m_BoxWidth = 40;
    
public:
    double power = 0;
    GLfloat vector[3] = { 0.0,0.0,0.0 };
    GLfloat color[4] = {1.0,1.0,1.0,1.0};
    bool is_Existence = true;
    //玉の番号を付与
    void setId(int id){
        m_id = id;
    }
    
    
    int getId(){
        return m_id;
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
        position->x = position->x + vector[0];
        position->y = position->y + vector[1];
        position->z = position->z + vector[2];
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
        if(position->x < 0.0){
            if(position -> z > 2 && position -> z <18){
            	
                //更に斜めの処理が入れば完璧
                setPosition(0.01f, position->y, position->z);
            	setPositionPro(-vector[0], vector[1], vector[2]);
            }
        }
        //right
        if(position->x > m_BoxWidth){
            if(position -> z > 2 && position -> z <18){
                setPosition(m_BoxWidth-0.01f, position->y, position->z);
                setPositionPro(-vector[0], vector[1], vector[2]);
            }
        }
        
        //UP(２つ）
        //2より大きく
        if(position -> x > 2.0f && position -> x < 19 && position->z < 0.0f){
            setPosition(position->x, position->y, 0.01f);
            setPositionPro(vector[0], vector[1], -vector[2]);
        }
        
        if(position -> x > 21 && position->x < m_BoxWidth-2 &&position->z < 0.0f){
            setPosition(position->x, position->y, 0.01f);
            setPositionPro(vector[0], vector[1], -vector[2]);
        }
        
        //DOWN(２つ）
        //2より大きく
        if(position -> x > 2.0f && position -> x < 19 && position->z > 20.0f){
            setPosition(position->x, position->y, 19.9f);
            setPositionPro(vector[0], vector[1], -vector[2]);
        }
        
        if(position -> x > 21 && position->x < m_BoxWidth-2 &&position->z > 20.0f){
            setPosition(position->x, position->y, 19.9f);
            setPositionPro(vector[0], vector[1], -vector[2]);
        }

    }
    
    void inPocket(){
        printf("pockets IN");
        is_Existence = false;
        score += combo * m_id;
    }
    
    //穴に当たったときの挙動
    void collisionPockets(){
        //左上Pocket
        if(position -> x > -2.0f && position -> x < 0.0f){
            if(position -> z < 0.0f){
                inPocket();
            }
            else if(position -> z > 20.0f){
                inPocket();
            }
        }
        
        if(position -> x > 19.0f && position -> x < 22.0f){
            if(position -> z < 0.0f){
                inPocket();
            }
            else if(position -> z > 20.0f){
                inPocket();
            }
        }
        
        if(position -> x > 40.0f && position -> x < 42.0f){
            if(position -> z < 0.0f){
                inPocket();
            }
            else if(position -> z > 20.0f){

                inPocket();
            }
        }
        
        
    }
};