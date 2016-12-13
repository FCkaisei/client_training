#include <stdio.h>
#include <iostream>
#include <GLUT/GLUT.h>
#ifndef __GAMEVALUE_H_INCLUDED__
#define __GAMEVALUE_H_INCLUDED__
/*
 Gameで共有して持っておきたい情報をまとめています.
 */
extern float ballAngle;
extern float rcos;
extern float rsin;
extern float shotPower;

//score
extern int score;

extern int ballNum;

//弾を連続で落としたときのコンボ
extern int combo;

#endif
