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
extern int firstCollision;
//弾を連続で落としたときのコンボ
extern int combo;
extern std::string gameStateLabel;
extern std::string gameStateLabelMiss;
extern std::string powerLabel;


extern float material_ambient[4];
extern float material_diffuse[4];
extern float material_specular[4];
extern float material_shinness;

#endif
