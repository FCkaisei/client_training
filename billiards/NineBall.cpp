#include <iostream>
#include <GLUT/GLUT.h>
#include "head/Nineball.h"
/*
 9ボール生成用のクラス.ballを管理
 */

//ballColor設定
GLfloat colorArray[9][4] ={
    //yellow
    {1.0,1.0,1.0,1.0},
    //blue
    {0.0,0.5,1.0,1.0},
    //red
    {1.0,0.0,0.0,1.0},
    //purple
    {1.0,0.0,1.0,1.0},
    //orange
    {1.0,0.7,0.0,1.0},
    //green
    {0.0,0.7,0.0,1.0},
    //wineRed
    {0.5,0.0,0.2,1.0},
    //black
    {0.0,0.0,0.0,1.0},
    //yellow2
    {1.0,1.0,0.0,1.0}
};
    
//初期設定値
GLfloat ballPositionArray[9][4] ={
    //中央
    {22.5,0.0,7.5},
    {22.5,0.0,6.5},
    {22.5,0.0,8.5},
    {21.5,0.0,7.0},
    {21.5,0.0,8.0},
    {23.5,0.0,7.0},
    {23.5,0.0,8.0},
    {20.5,0.0,7.5},
    {24.5,0.0,7.5}
};
    
NineBall::NineBall(){
    ballObject1 = *new BallObject;
    ballObject2 = *new BallObject;
    ballObject3 = *new BallObject;
    ballObject4 = *new BallObject;
    ballObject5 = *new BallObject;
    ballObject6 = *new BallObject;
    ballObject7 = *new BallObject;
    ballObject8 = *new BallObject;
    ballObject9 = *new BallObject;
    BallObject balla[9] = {ballObject1,ballObject2,ballObject3,ballObject4,ballObject5,ballObject6,ballObject7,ballObject8,ballObject9};
    for(int i = 0; i<9; i++){
        ball[i] = balla[i];
    }
    for(int i = 0; i<9; i++){
        ball[i].setId(i);
        ball[i].setForm(0.5f,16.0f,16.0f);
        ball[i].setPosition(ballPositionArray[i][0],ballPositionArray[i][1],ballPositionArray[i][2]);
        ball[i].setColor(colorArray[i][0],colorArray[i][1],colorArray[i][2],colorArray[i][3]);
    }
}
