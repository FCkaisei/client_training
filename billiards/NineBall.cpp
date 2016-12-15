#include <iostream>
#include <GLUT/GLUT.h>
#include "head/Nineball.h"
/*
 9ボール生成用のクラス.ballを管理
 */

//ballColor設定
GLfloat colorArray[10][4] ={
    //自分の玉
    {1.0f,1.0f,1.0f,1.0f},
    //1番
    {1.0f,1.0f,0.0f,1.0f},
    //2番
    {0.0f,0.5f,1.0f,1.0f},
    //3番
    {1.0f,0.0f,0.0f,1.0f},
    //4番
    {1.0f,0.0f,1.0f,1.0f},
    //5番
    {1.0f,0.5f,0.0f,1.0f},
    //6番
    {0.0f,0.7f,0.0f,1.0f},
    //7番
    {1.0f,0.3f,0.3f,1.0f},
    //8番
    {0.0f,0.0f,0.0f,1.0f},
    //9番
    {1.0f,0.7f,0.3f,1.0f},
};

//青1.0,01.,1.0,1.0
//赤1.0,0.0,0.0,1.0
//紫1.0,0.0,1.0,1.0
//orange1.0,0.0,1.0,1.0
//初期設定値
GLfloat ballPositionArray[10][4] ={
    //自分の玉
    {10.0f,0.0f,10.0f},
    //1番目
    
    {20.5f,0.0f,10.0f},
    //2番目
    {22.5f,0.0f,11.0f},
    //3番目
    
    {24.5f,0.0f,10.0f},
    //4番目
    {22.5f,0.0f,9.0f},
    //5番目
    {21.5f,0.0f,10.5f},
    //6番目
    {21.5f,0.0f,9.5f},
    //7番目
    {23.5f,0.0f,10.5f},
    //8番目
    {23.5f,0.0f,9.5f},
    //9番目
    {22.5f,0.0f,10.0f},
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
    ballObject10 = *new BallObject;
    BallObject balla[10] = {ballObject1,ballObject2,ballObject3,ballObject4,ballObject5,ballObject6,ballObject7,ballObject8,ballObject9,ballObject10};
    for(int i = 0; i<ballNum; i++){
        ball[i] = balla[i];
    }
    for(int i = 0; i<ballNum; i++){
        ball[i].setId(i);
        ball[i].setForm(0.5f,16.0f,16.0f);
        ball[i].setPosition(ballPositionArray[i][0],ballPositionArray[i][1],ballPositionArray[i][2]);
        ball[i].setColor(colorArray[i][0],colorArray[i][1],colorArray[i][2],colorArray[i][3]);
    }
    
}
void NineBall::ResetAll(){
    
    ballObject1 = *new BallObject;
    ballObject2 = *new BallObject;
    ballObject3 = *new BallObject;
    ballObject4 = *new BallObject;
    ballObject5 = *new BallObject;
    ballObject6 = *new BallObject;
    ballObject7 = *new BallObject;
    ballObject8 = *new BallObject;
    ballObject9 = *new BallObject;
    BallObject balla[10] = {ballObject1,ballObject2,ballObject3,ballObject4,ballObject5,ballObject6,ballObject7,ballObject8,ballObject9,ballObject10};
    for(int i = 0; i<ballNum; i++){
        ball[i] = balla[i];
    }
    for(int i = 0; i<ballNum; i++){
        ball[i].setId(i);
        ball[i].setForm(0.5f,16.0f,16.0f);
        ball[i].setPosition(ballPositionArray[i][0],ballPositionArray[i][1],ballPositionArray[i][2]);
        ball[i].setColor(colorArray[i][0],colorArray[i][1],colorArray[i][2],colorArray[i][3]);
    }
};
