#include <iostream>
#include <GLUT/GLUT.h>
#ifndef __LABEL2D_H_INCLUDED__
#define __LABEL2D_H_INCLUDED__
class Label2D{
public:
	void display2D(std::string str, float x, float y);
	void display2D(std::string str, float x, float y,float z);
};

#endif
