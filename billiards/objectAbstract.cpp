#include <iostream>
#include <GLUT/GLUT.h>
#pragma once

//3DObject類の基底クラス。
//3DObjectを作るときは継承してね
//表:表ABS:ObjectABSがおすすめ
class ObjectAbs{
public:
		virtual void setForm(float w, float d, float h) = 0;
		virtual void getForm(GLfloat *p)= 0;
		virtual void getPosition(GLfloat *p)= 0;
		virtual void setPosition(float x, float y, float z)= 0;
		virtual void Draw(void) = 0;
};
