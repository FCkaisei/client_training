#include <iostream>
#include <GLUT/GLUT.h>
#ifndef __POCKETS_H_INCLUDED__
#define __POCKETS_H_INCLUDED__

class Pockets{
public:
    Vector();
    Vector(float _x,float _y,float _z);
    // =Vectorで値を入れることができる
    // &は参照渡し
    Vector& operator=(const Vector& v);
    Vector& operator+=(const Vector& v);
    Vector& operator-=(const Vector& v);
    Vector& operator*=(float k);
    Vector& operator/=(float k);
    Vector operator+();
    Vector operator-();
    float getX();
    float x;
    float y;
    float z;
};


//2項演算子
Vector operator+(const Vector& u,const Vector& v);
Vector operator-(const Vector& u,const Vector& v);
float operator*(const Vector& u,const Vector& v);
Vector operator*(const Vector& v, float k);
Vector operator*(float k ,const Vector& v);
Vector operator/(const Vector& v, float k);

//画面への出力
#include <iostream>
std::ostream& operator<<(std::ostream& stream, const Vector& v);

#endif