#include <iostream>
#include <GLUT/GLUT.h>
#ifndef __VECTOR_H_INCLUDED__
#define __VECTOR_H_INCLUDED__

/*
 *Vectorクラス
 *参考URL:http://d.hatena.ne.jp/white_wheels/20100304/p2
 */
class Vector{
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
