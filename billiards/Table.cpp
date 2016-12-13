#include <iostream>
#include <GLUT/GLUT.h>
#include <map>
#include "objectAbstract.cpp"
#include "BoxObject.cpp"
#include "PocketObject.cpp"
#pragma once
using namespace std;
class Table{
public:
    PocketObject hall1,hall2,hall3,hall4,hall5,hall6,hall7,hall8,hall9,hall10,hall11,hall12,hall13,hall14;
    PocketObject hall[14] = {hall1, hall2, hall3, hall4, hall5, hall6,hall7,hall8,hall9,hall10,hall11,hall12,hall13,hall14};
    
    BoxObject tableBase,boxObject1,boxObject2,boxObject3,boxObject4,boxObject5,boxObject6;
    BoxObject box[7] = {tableBase,boxObject1,boxObject2, boxObject3, boxObject4,boxObject5,boxObject6};
    
    //positon初期設定値
    GLfloat boxPositionArray[7][3] ={
        // 青い土台部
        {0.0f,-1.5f,0.0f},
        //←3
        {-2.0,-1.0f,2.0f},
        //→4
        {40.0f,-1.0f,2.0f},
        //左上1
        {2.0f,-1.0f,-2.0f},
        //右上2
        {21.0f,-1.0f,-2.0f},
        //5
        {2.0f,-1.0f,20.0f},
        //6
        {21.0f,-1.0f,20.0f},
        
    };
   
    //Forms初期設定値
    GLfloat boxFormArray[7][4] ={
        //青い土台
        {40.0,20.0,1.0,40.0},
        
        //←3
        {2.0f,16.0f,2.0f,2.0},
        //4→
        {2.0f,16.0f,2.0f,2.0f},
        //1↑
        {17.0,2.0,2.0,17.0},
        //2
        {17.0,2.0,2.0,17.0},
        //5
        {17.0,2.0,2.0,17.0},
        //6
        {17.0,2.0,2.0,17.0},
    };
    
    GLfloat boxAngleArray[7][4]{
        {0.0,0.0,0.0,0.0},
        
        //←
        {0.0,0.0,0.0,0.0},
        //→
        {0.0,0.0,0.0,0.0},
        //↑
        {0.0,0.0,0.0,0.0},
        {0.0,0.0,0.0,0.0},
        //↓
        {0.0,0.0,0.0,0.0},
        {0.0,0.0,0.0,0.0},
        
    };
    
    GLfloat boxColorArray[7][4] ={
        //blue
        {0.0,0.5,1.0,1.0},
        //orange
        {1.0,0.7,0.0,1.0},
        //orange
        {1.0,0.7,0.0,1.0},
        //orange
        {1.0,0.7,0.0,1.0},
        //orange
        {1.0,0.7,0.0,1.0},
        //orange
        {1.0,0.7,0.0,1.0},
        //orange
        {1.0,0.7,0.0,1.0},
    };
    
    
    
    //hallPositon初期設定値
    GLfloat hallPositionArray[14][4] ={
        //左上
        {-2.0f,-1.0f,-2.0f},
        {0.0f,-1.0f,-2.0f},
        {-2.0f,-1.0f,0.0f},
        
        //↑真ん中
        {19.0f,-1.0,-2.0},
        //右上
        {38.0,-1.0,-2.0},
        {40.0,-1.0,-2.0},
        {40.0,-1.0,0.0},
        
        
        //左下
        {0.0f,-1.0,20.0f},
        
        {-2.0f,-1.0,20.0f},
        {-2.0f,-1.0,18.0f},
        
        //真ん中下
        {19.0,-1.0,20.0f},
        
        //右下
        {38.0,-1.0,20.0f},
        {40.0,-1.0,20.0f},
        {40.0,-1.0,18.0f},
        
        
        
        
    };
    /*
     

     
     */
    
    //Forms初期設定値
    GLfloat hallFormArray[14][4] ={
        {2.0,2.0,2.0,2.0},
		{2.0,2.0,2.0,2.0},
        {2.0,2.0,2.0,2.0},
        {2.0,2.0,2.0,2.0},
        {2.0,2.0,2.0,2.0},
        {2.0,2.0,2.0,2.0},
        {2.0,2.0,2.0,2.0},
        {2.0,2.0,2.0,2.0},
        {2.0,2.0,2.0,2.0},
        {2.0,2.0,2.0,2.0},
        {2.0,2.0,2.0,2.0},
        {2.0,2.0,2.0,2.0},
        {2.0,2.0,2.0,2.0},
        {2.0,2.0,2.0,2.0},
    };
    
    GLfloat hallAngleArray[14][4]{
        {0.0,0.0,0.0,0.0},
        
        //←
        {0,0.0,0.0,0.0},
        //→
        {0.0,0.0,0.0,0.0},
        //↑
        {0.0,0.0,0.0,0.0},
        {0.0,0.0,0.0,0.0},
        //↓
        {0.0,0.0,0.0,0.0},
        {0.0,0.0,0.0,0.0},
        {0.0,0.0,0.0,0.0},
        {0.0,0.0,0.0,0.0},
        {0.0,0.0,0.0,0.0},
        {0.0,0.0,0.0,0.0},
        {0.0,0.0,0.0,0.0},
        {0.0,0.0,0.0,0.0},
        {0.0,0.0,0.0,0.0},
    };
    
    GLfloat hallColorArray[14][4] ={
        {0.0,1.0,0.0,1.0},
        {0.0,1.0,0.0,1.0},
        {0.0,1.0,0.0,1.0},
        {0.0,1.0,0.0,1.0},
        {0.0,1.0,0.0,1.0},
        {0.0,1.0,0.0,1.0},
        {0.0,1.0,0.0,1.0},
        {0.0,1.0,0.0,1.0},
        {0.0,1.0,0.0,1.0},
        {0.0,1.0,0.0,1.0},
        {0.0,1.0,0.0,1.0},
        {0.0,1.0,0.0,1.0},
        {0.0,1.0,0.0,1.0},
        {0.0,1.0,0.0,1.0},
    };
    
   void SetTable(){
        for(int i = 0; i<7; i++){
            box[i].setForm(
                           boxFormArray[i][0],
                           boxFormArray[i][1],
                           boxFormArray[i][2],
                           boxFormArray[i][3]
                           );
            
            box[i].setPosition(
                               boxPositionArray[i][0],
                               boxPositionArray[i][1],
                               boxPositionArray[i][2]
                               );
            
            box[i].SetColor(
                            boxColorArray[i][0],
                            boxColorArray[i][1],
                            boxColorArray[i][2],
                            boxColorArray[i][3]
                            );
            
            box[i].setAngle(
                            boxAngleArray[i][0],
                            boxAngleArray[i][1],
                            boxAngleArray[i][2],
                            boxAngleArray[i][3]
                            );
        }
       
       for(int i = 0; i< 14; i++){
           hall[i].setPosition(
                               hallPositionArray[i][0],
                               hallPositionArray[i][1],
                               hallPositionArray[i][2]
           );
           hall[i].setForm(
                          hallFormArray[i][0],
                          hallFormArray[i][1],
                          hallFormArray[i][2],
                          hallFormArray[i][3]
                          );
           
           hall[i].SetColor(
                           hallColorArray[i][0],
                           hallColorArray[i][1],
                           hallColorArray[i][2],
                           hallColorArray[i][3]
                           );
           
           hall[i].setAngle(
                           hallAngleArray[i][0],
                           hallAngleArray[i][1],
                           hallAngleArray[i][2],
                           hallAngleArray[i][3]
                           );
           
       }
    }
    void CreateTable(){
        //土台を作る
        for(int i = 0; i < 7; i++){
            glMaterialfv(GL_FRONT,GL_DIFFUSE, box[i].color);
            glPushMatrix();
            box[i].Draw();
            glPopMatrix();
        }
        
        for(int i = 0; i < 14; i++){
            glMaterialfv(GL_FRONT,GL_DIFFUSE, hall[i].color);
            glPushMatrix();
            hall[i].Draw();
            glPopMatrix();
        }
    }
};
