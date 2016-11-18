#include "head/Vector.h"

Vector::Vector():x(0),y(0)
{
}

Vector::Vector(float _x,float _y):x(_x),y(_y)
{
}
//代入演算子の定義
Vector& Vector::operator=(const Vector& v){
    this->x=v.x;	this->y=v.y;
    return *this;
}
// +=の定義
Vector& Vector::operator+=(const Vector& v){
    this->x += v.x;	this->y += v.y;	return *this;
}
// -=の定義
Vector& Vector::operator-=(const Vector& v){
    this->x -= v.x;	this->y -= v.y;	return *this;
}
// *=の定義
Vector& Vector::operator*=(float k){
    this->x *= k;	this->y *= k;	return *this;
}
// /=の定義
Vector& Vector::operator/=(float k){
    this->x /= k;	this->y /= k;	return *this;
}

//+の定義:	+v
Vector Vector::operator+(){
    return *this;
}
//-の定義:	-v
Vector Vector::operator-(){
    return Vector(-x,-y);
}


//二項演算子
Vector operator+(const Vector& u,const Vector& v){	//vector+vector
    Vector w;
    w.x = u.x + v.x;
    w.y = u.y + v.y;
    return w;
}

Vector operator-(const Vector& u,const Vector& v){	//vector-vector
    Vector w;
    w.x = u.x - v.x;
    w.y = u.y - v.y;
    return w;
}

float operator*(const Vector& u,const Vector& v){	//内積 vector*vector
    return u.x * v.x + u.y * v.y;
}

Vector operator*(const Vector& v, float k){	//vector*scalar
    Vector w;
    w.x = v.x * k;
    w.y = v.y * k;
    return w;
}
Vector operator*(float k ,const Vector& v){	//scalar*vector
    Vector w;
    w.x = v.x * k;
    w.y = v.y * k;
    return w;
}
Vector operator/(const Vector& v, float k){	//vector/scalar
    Vector w;
    w.x = v.x / k;
    w.y = v.y / k;
    return w;
}

//画面への出力
#include <iostream>
using namespace std;
ostream& operator<<(ostream& stream, const Vector& v){
    return stream <<'('<<v.x<<","<<v.y<<')';
}