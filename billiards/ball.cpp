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
    //球の番号
    int m_id = 0;
    double m_BoxHeight = 20;
    double m_BoxWidth = 40;
    
public:
    //power
    double power = 0;
    
    GLfloat vector[3] = { 0.0,0.0,0.0 };
    GLfloat color[4] = {1.0,1.0,1.0,1.0};
    //移動しているか
    bool is_move = false;
    //存在しているか
    bool is_Existence = true;
    
    
    //玉の番号を付与
    void setId(int id){
        m_id = id;
    }
    //idを返す
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
    
    //Schott時Powerを初速となるパワーを取得する
    void setPower(double d){
        power = d;
    }
    
    //方向を決めて値を入れる
    void setVectorPower(GLfloat uni[]){
        vector[0] = (float)(uni[0]*power);
        vector[1] = (float)(uni[1]*power);
        vector[2] = (float)(uni[2]*power);
    }
    
    //減速処理
    void Physics(){
        vector[0] =vector[0] * 0.98f;
        vector[1] =vector[1] * 0.98f;
        vector[2] =vector[2] * 0.98f;
        if(std::abs(vector[0]) < 0.01){
            
            if(std::abs(vector[2]) < 0.01){
                vector[0] = 0;
                vector[1] = 0;
                vector[2] = 0;
                is_move  =false;
            }
            else{
                is_move  =true;
            }
        }
        else{
            is_move = true;
        }
    }
    
    //positionの移動
    void movePosition(){
        position->x = position->x + vector[0] * 0.3;
        position->y = position->y + vector[1] * 0.3;
        position->z = position->z + vector[2] * 0.3;
    }
    
    void setPosition(float x, float y, float z){
        position->x = x;
        position->y = y;
        position->z = z;
    }
    
    void setVector(float x, float y, float z){
        vector[0] = x;
        vector[1] = y;
        vector[2] = z;
    }
    
    GLfloat getPosition_x(){
        return position->x;
    }
    GLfloat getPosition_y(){
        return position->y;
    }
    GLfloat getPosition_z(){
        return position->z;
    }
    GLfloat getVector_x(){
        return vector[0];
    }
    GLfloat getVector_z(){
        return vector[0];
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
            	setVector(-vector[0], vector[1], vector[2]);
            }
        }
        
        //right
        if(position->x > m_BoxWidth){
            if(position -> z > 2 && position -> z <18){
                setPosition(m_BoxWidth-0.01f, position->y, position->z);
                setVector(-vector[0], vector[1], vector[2]);
            }
        }
        //UP(２つ）
        //2より大きく
        if(position -> x > 2.0f && position -> x < 19 && position->z < 0.0f){
            setPosition(position->x, position->y, 0.01f);
            setVector(vector[0], vector[1], -vector[2]);
        }
        
        if(position -> x > 21 && position->x < m_BoxWidth-2 &&position->z < 0.0f){
            setPosition(position->x, position->y, 0.01f);
            setVector(vector[0], vector[1], -vector[2]);
        }
        
        //DOWN(２つ）
        //2より大きく
        if(position -> x > 2.0f && position -> x < 19 && position->z > 20.0f){
            setPosition(position->x, position->y, 19.9f);
            setVector(vector[0], vector[1], -vector[2]);
        }
        
        if(position -> x > 21 && position->x < m_BoxWidth-2 &&position->z > 20.0f){
            setPosition(position->x, position->y, 19.9f);
            setVector(vector[0], vector[1], -vector[2]);
        }

    }
    
    void inPocket(){
        printf("pockets IN");
        is_Existence = false;
        is_move = false;
        vector[0] = 0.0f;
        vector[1] = 0.0f;
        vector[2] = 0.0f;
        score += combo * m_id;
    }
    
    //穴に当たったときの挙動
    void collisionPockets(){
        
        //左上Pocket
        if(position -> x > -2.0f && position -> x < 2.0f){
            
            if(position -> z < 0.0f){
                inPocket();
            }
            else if(position -> z > 20.0f){
                inPocket();
            }
        }
        if(position->x < 0.0f){
            if(position -> z < 2.0f){
                inPocket();
            }
            else if(position -> z > 18.0f){
                inPocket();
            }
        }
        
        //中央
        if(position -> x > 19.0f && position -> x < 22.0f){
            if(position -> z < 0.0f){
                inPocket();
            }
            else if(position -> z > 20.0f){
                inPocket();
            }
        }
        
        //右Pocket
        if(position -> x > 38.0f && position -> x < 42.0f){
            if(position -> z < 0.0f){
                inPocket();
            }
            else if(position -> z > 20.0f){
                inPocket();
            }
        }
        
        if(position->x >40){
            if(position -> z < 2.0f){
                inPocket();
            }
            else if(position -> z > 18){
                inPocket();
            }
        }
        
        
    }
};
