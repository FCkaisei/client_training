#include "head/Vector.h"


//何も受け取らなかったとき、値を0とする
Vector::Vector():x(0),y(0),z(0){
}

//受け取った値をそれぞれx,y,zに入れる
Vector::Vector(float _x,float _y, float _z):x(_x),y(_y),z(_z){
}

float Vector::getX(){
    return this->x;
}

//代入演算子の定義
Vector& Vector::operator=(const Vector& v){
    this->x=v.x;
    this->y=v.y;
    this->z=v.z;
    return *this;
}

// +=の定義
Vector& Vector::operator+=(const Vector& v){
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    return *this;
}
// -=の定義
Vector& Vector::operator-=(const Vector& v){
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
    return *this;
}
// *=の定義
Vector& Vector::operator*=(float k){
    this->x *= k;
    this->y *= k;
    this->z *= k;
    return *this;
}
// /=の定義
Vector& Vector::operator/=(float k){
    this->x /= k;
    this->y /= k;
    this->z /= k;
    return *this;
}

//+の定義:	+v
Vector Vector::operator+(){
    return *this;
}

//-の定義:	-v
Vector Vector::operator-(){
    return Vector(-x,-y,-z);
}


//二項演算子

//vector+vector
Vector operator+(const Vector& u,const Vector& v){
    Vector w;
    w.x = u.x + v.x;
    w.y = u.y + v.y;
    w.z = u.z + v.z;
    return w;
}

//vector-vector
Vector operator-(const Vector& u,const Vector& v){
    Vector w;
    w.x = u.x - v.x;
    w.y = u.y - v.y;
    w.z = u.z - v.z;
    return w;
}

//内積 vector*vector
float operator*(const Vector& u,const Vector& v){
    return u.x * v.x + u.y * v.y;
}

//vector*scalar
Vector operator*(const Vector& v, float k){
    Vector w;
    w.x = v.x * k;
    w.y = v.y * k;
    w.z = v.z * k;
    return w;
}

//scalar*vector
Vector operator*(float k ,const Vector& v){
    Vector w;
    w.x = v.x * k;
    w.y = v.y * k;
    w.z = v.z * k;
    return w;
}

//vector/scalar
Vector operator/(const Vector& v, float k){
    Vector w;
    w.x = v.x / k;
    w.y = v.y / k;
    w.z = v.z / k;
    return w;
}

//画面への出力
#include <iostream>
using namespace std;
ostream& operator<<(ostream& stream, const Vector& v){
    return stream <<'('<<v.x<<","<<v.y<<","<<v.z<<')';
}
