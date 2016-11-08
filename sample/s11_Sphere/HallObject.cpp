#include <stdio.h>
#include <GLUT/GLUT.h>
#include <vector>
#include <cmath>
#include "objectAbstract.cpp"
class HallObject : public ObjectAbs{
public:
    
    int face[6][4] = {
        { 0, 1, 2, 3 },
        { 1, 5, 6, 2 },
        { 5, 4, 7, 6 },
        { 4, 0, 3, 7 },
        { 4, 5, 1, 0 },
        { 3, 2, 6, 7 }
    };
    
    GLdouble normal[6][3] = {
        { 0.0, 0.0,-1.0 },
        { 1.0, 0.0, 0.0 },
        { 0.0, 0.0, 1.0 },
        {-1.0, 0.0, 0.0 },
        { 0.0,-1.0, 0.0 },
        { 0.0, 1.0, 0.0 }
    };
    
    GLfloat color[4] = {1.0,1.0,1.0,1.0};
    void SetColor(float R,float G,float B,float A){
        color[0] = R;
        color[1] = G;
        color[2] = B;
        color[3] = A;
    }
    
    void setForm(GLfloat w, GLfloat d, GLfloat h){
        width = w;
        depth = d;
        height = h;
        width2 = w;
    }
    
    
    void setForm(GLfloat w, GLfloat d, GLfloat h,GLfloat w2){
        width = w;
        depth = d;
        height = h;
        width2 = w2;
    }
    
    void getForm(GLfloat *p){
        //GLfloat form[3] = {width,height,depth};
    }
    
    void getPosition(GLfloat *p){
        GLfloat position[] = { positionX, positionY, positionZ };
        GLfloat* p_position;
        
        p_position = position;
    }
    
    
    void setPosition(float x, float y, float z){
        positionX = x;
        positionY = y;
        positionZ = z;
    }
    
    void setAngle(float ang, float x, float y, float z){
        angle = ang;
        angleX = x;
        angleY = y;
        angleZ = z;
    }
    
    void Draw(void){
        glTranslatef(positionX,positionY,positionZ);
        float hoge = (width-width2)/2;
        
        GLdouble vertex[8][3] = {
            { 0.0, 0.0, 0.0 }, /* A */
            { width, 0.0, 0.0 }, /* B */
            { width, height, 0.0 }, /* C */
            { 0.0, height, 0.0 }, /* D */
            
            { hoge, 0.0, depth }, /* E */
            { hoge+width2, 0.0, depth }, /* F */
            { hoge+width2, height, depth }, /* G */
            { hoge, height, depth }  /* H */
        };
        
        int i;
        int j;
        glRotated(angle, angleX, angleY, angleZ);
        glBegin(GL_QUADS);
        for (j = 0; j < 6; ++j) {
            glNormal3dv(normal[j]);
            for (i = 0; i < 4; ++i) {
                glVertex3dv(vertex[face[j][i]]);
            }
        }
        glEnd();
    }
    
private:
    GLfloat all[4] = {0.0,0.0,0.0,0.0};
    float angle;
    float angleX;
    float angleY;
    float angleZ;
    float width;
    float width2;
    float height;
    float depth;
    float positionX;
    float positionY;
    float positionZ;
    
};
