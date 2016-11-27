#include <iostream>
#include <GLUT/GLUT.h>
#include "../Ball.cpp"
#ifndef __NINEBALL_H_INCLUDED__
#define __NINEBALL_H_INCLUDED__

/*
 *Vectorクラス
 *参考URL:http://d.hatena.ne.jp/white_wheels/20100304/p2
 */
class NineBall{
public:
    NineBall();
    BallObject ballObject1;
    BallObject ballObject2;
    BallObject ballObject3;
    BallObject ballObject4;
    BallObject ballObject5;
    BallObject ballObject6;
    BallObject ballObject7;
    BallObject ballObject8;
    BallObject ballObject9;
    BallObject ball[9];
};

extern GLfloat ballPositionArray[9][4];
extern GLfloat colorArray[9][4];
extern BallObject *ballObject1,*ballObject2,*ballObject3,*ballObject4,*ballObject5,*ballObject6,*ballObject7,*ballObject8,*ballObject9;

#endif