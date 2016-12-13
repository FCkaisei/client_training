#include <GLUT/GLUT.h>
#include <math.h>
#include "head/WindowManager.h"


//ウィンドウの比率の固定などに利用
void windowManager::resize(int w, int h){
    glViewport(0,0,w,h);
    //透視変換行列の設定
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f, (float)w / (float)h, 1.0f, 100.0f);
    //モデルビュー変換行列の設定
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3.0f, 4.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}
