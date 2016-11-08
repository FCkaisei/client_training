#include <stdio.h>
#include <GLUT/GLUT.h>
#include <vector>
#include <cmath>

class ColorObject{
public:
    //ボール色
    GLfloat yellow[4]       = { 1.0, 1.0, 0.0, 1.0 };
    GLfloat blue[4]         = { 0.2, 0.2, 0.8, 1.0 };
    GLfloat red[4]          = { 0.8, 0.2, 0.2, 1.0 };
    GLfloat purple[4]       = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat orange[4]       = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat green[4]        = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat wineRed[4]      = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat black[4]        = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat yellow2[4]      = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat blue2[4]        = { 0.2, 0.2, 0.8, 1.0 };
    GLfloat red2[4] 		= { 0.8, 0.2, 0.2, 1.0 };
    GLfloat purple2[4]      = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat orange2[4]      = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat green2[4]       = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat wineRed2[4]     = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat black2[4]       = { 0.0, 1.0, 0.0, 1.0 };
    
    //自球の色
    GLfloat white[4]        = { 1.0, 1.0, 1.0, 1.0 };
    
    //土台枠色
    GLfloat wood[4]         = { 1.0, 0.65, 0.49, 1.0 };
    
    //台色
    GLfloat whiteBlue[4] 	= { 1.0, 0.65, 0.49, 1.0 };
    
};
