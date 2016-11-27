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
    PocketObject hall1,hall2,hall3,hall4,hall5,hall6;
    PocketObject hall[6] = {hall1, hall2, hall3, hall4, hall5, hall6 };
    
    BoxObject tableBase,boxObject1,boxObject2,boxObject3,boxObject4,boxObject5,boxObject6;
    BoxObject box[7] = {tableBase,boxObject1,boxObject2, boxObject3, boxObject4,boxObject5,boxObject6};
    
    //positon初期設定値
    GLfloat boxPositionArray[7][3] ={
        //土台
        {-3.0,-1.5,-3.0},
        //←
        {-2.5,-1.0,15.0},
        //→
        {32.5,-1.0,0.0},
        //↑
        {0.0,-1.0,-2.5},
        {15.0,-1.0,-2.5},
        //↓
        {30.0,-1.0,17.5},
        {15.0,-1.0,17.5},
        
    };
   
    //Forms初期設定値
    GLfloat boxFormArray[7][4] ={
        {40.0,23.0,1.0,40.0},
        //←
        {15.0,2.5,2.0,10.0},
        //→
        {15.0,2.5,2.0,10.0},
        //↑
        {13.0,2.5,2.0,10.0},
        {13.0,2.5,2.0,10.0},
        
        //↓
        {13.0,2.5,2.0,10.0},
        {13.0,2.5,2.0,10.0},
    };
    
    GLfloat boxAngleArray[7][4]{
        {0.0,0.0,0.0,0.0},
        
        //←
        {-270,0.0,1.0,0.0},
        //→
        {-90.0,0.0,1.0,0.0},
        //↑
        {0.0,0.0,0.0,0.0},
        {0.0,0.0,0.0,0.0},
        //↓
        {180.0,0.0,1.0,0.0},
        {180.0,0.0,1.0,0.0},
        
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
    GLfloat hallPositionArray[6][4] ={
        //土台
        {0.0f,0.0f,0.0f},
        //←
        {-2.5,-1.0,15.0},
        //→
        {32.5,-1.0,0.0},
        //↑
        {15.0,0.0,15.0},
        //{0.0,-1.0,-2.5},
        {15.0,-1.0,-2.5},
        //↓
        {30.0,-1.0,17.5},
        
        
    };
    /*
     

     
     */
    
    //Forms初期設定値
    GLfloat hallFormArray[6][4] ={
        {1.0,1.0,1.0,1.0},
		{1.0,1.0,1.0,1.0},
        {1.0,1.0,1.0,1.0},
        {1.0,1.0,1.0,1.0},
        {1.0,1.0,1.0,1.0},
        {1.0,1.0,1.0,1.0},
    };
    
    GLfloat hallAngleArray[6][4]{
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
        
    };
    
    GLfloat hallColorArray[6][4] ={
        //orange
        {0.0,1.0,0.0,1.0},
        //orange
        {0.0,0.0,0.0,1.0},
        //orange
        {0.0,0.0,0.0,1.0},
        //orange
        {0.0,0.0,0.0,1.0},
        //orange
        {0.0,0.0,0.0,1.0},
        //orange
        {0.0,0.0,0.0,1.0},
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
       for(int i = 0; i< 6; i++){
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
};