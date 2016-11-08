#include <stdio.h>
#include <iostream>
#include <string>
#include <GLUT/GLUT.h>
#include <vector>
#include <cmath>
#include <math.h>
#include "ColorObject.cpp"
#include "Table.cpp"
#include "SixBall.cpp"
#include "KumaEngine.cpp"
#include "GameManager.cpp"

Table table;
SixBall sixball;
BallObject ballObj1;
ColorObject colorObject;
PlayerOperationState GameManager::p_OperationState;
GLfloat p_position[] = { 0.0,0.0,0.0 };
GLfloat unitVec[] = { 0.0,0.0,0.0 };
double r = 0; /* 回転角 */
double rcos;
double rsin;
double power = 0;

double pow(double p){
    p = p*p;
    return p;
}

void idle(void){
  glutPostRedisplay();
}

//Viewの設定をしますここで全部設定しちゃえ
void createView(){
    /* 視点位置と視線方向 */
    gluLookAt(
              (float)p_position[0]+rsin, 3.0, (float)p_position[2]+rcos,
              (float)p_position[0], 0.0, (float)p_position[2],
              0.0, 1.0, 0.0);
}

void createView(GLfloat gl[]){
    /* 視点位置と視線方向 */
    
    /*
     カメラの位置（視点）のX位置を指定します。
     カメラが見ているところ（注視点）のX位置を指定します。
     カメラの上方向がX軸に対してどれくらいかを指定します。
     */
    gluLookAt(gl[0],gl[1],gl[2],
              15.0, 1.0, 7.5,
              0.0,3.0,0.0
    );
}

//光の設定全部個々でやっちゃえ！
void createLight(){
    /* 光源の位置設定 */
    GLfloat light0pos[] = { 0.0, 3.0, 5.0, 1.0 };
    GLfloat light1pos[] = { 5.0, 3.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
    
}

//Objectの描画
void createObj(){
    //クラスに分けるとりあえずこのまま　落ち着いたら変えよう
    table.SetTable();
    for(int i = 0; i < 7; i++){
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_DIFFUSE, table.box[i].color);
        table.box[i].Draw();
        glPopMatrix();
    }
    for(int i = 0; i < 6; i++){
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_DIFFUSE, table.hall[i].color);
        table.hall[i].Draw();
        glPopMatrix();
    }
    glFlush();
}

/*
 camera
 Light
 object
 */
void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    
    rcos = cos(r)*15;
    rsin = sin(r)*15;
    ballObj1.getPosition(p_position);
    GLfloat cameraPosition[] = {(float)(p_position[0]+rsin), 0.0, (float)(p_position[2]+rcos)};
    
    //ここはステート処理にしたい。だから外部にカメラをステートで管理するクラスをセットしようね。
    //全ての弾が止まったらカメラモードを変更　っていうか、弾が止まる操作不能にする必要がある
    GLfloat hoge2[] = {0.0,1.0,0.0};
    ballObj1.getVec(hoge2);
    
    if((hoge2[0] < 0.001 && hoge2[0] > -0.001) || (hoge2[2] < 0.001 && hoge2[2] > -0.001)){
        GameManager::setPlayerOperationState(PlayerOperationState::WAIT);
    }
    
    if(GameManager::getPlayerOperationState() == PlayerOperationState::WAIT){
        createView();
    }
    else{
        GLfloat hoge[] = {0.0,60.0,0.0};
        createView(hoge);
    }
    //LENGHTのとり方を検索しとけ
    for(int i = 0; i < 9; i++){
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_DIFFUSE, sixball.ball[i].color);
        sixball.ball[i].getPosition(p_position);
        sixball.ball[i].setPosition((float)(p_position[0]),(float)(p_position[1]),(float)(p_position[2]));
        sixball.ball[i].collisionDetectionBox();
        sixball.ball[i].Physics();
        for(int j = 0; j < 9; j++){
            if(i != j){
                sixball.ball[i].collisionDetection(sixball.ball[j]);
            }
            if(i == j){
                ballObj1.collisionDetection(sixball.ball[j]);
            }
            
        }
        sixball.ball[i].Draw();
        glPopMatrix();
    }
    
    
    /* 球の図形の描画 */
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorObject.white);
    
    //単位ベクトルの取得
    KumaEngine::UnitVector(p_position, cameraPosition, unitVec);
    
    ballObj1.getPosition(p_position);
    //positionをセット
    ballObj1.setPosition((float)(p_position[0]),(float)(p_position[1]),(float)(p_position[2]));
    ballObj1.collisionDetectionBox();
    //衝突判定
    ballObj1.collisionDetection(sixball.ball[2]);
    
    //描画
    ballObj1.Draw();
    
    //次の動作時減速するよ
    ballObj1.Physics();
    glPopMatrix();
    createLight();
    createObj();
}


void resize(int w, int h){
    
    /* 一周回ったら回転角を 0 に戻す */
    if (r >= 360){
        r = 0;
    }
    
	glViewport(0,0,w,h);

	/* 透視変換行列の設定 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0f, (float)w / (float)h, 1.0f, 100.0f);
	/* モデルビュー変換行列の設定 */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3.0f, 4.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}



void key(unsigned char key, int x, int y){
	switch (key) {
		case 'q':
		glutIdleFunc(idle);
            if(GameManager::getPlayerOperationState() == PlayerOperationState::WAIT){
                r += 0.2;
            }
			break;
		case 'w':
		glutIdleFunc(idle);
            if(GameManager::getPlayerOperationState() == PlayerOperationState::WAIT){
                r -= 0.2;
            }
			break;
		case 'e':
            if(GameManager::getPlayerOperationState() == PlayerOperationState::WAIT){
                GameManager::setPlayerOperationState(PlayerOperationState::SHOT);
                power = 1.2f;
                ballObj1.setPower(power);
                ballObj1.setProPower(unitVec);
                for(int i = 0; i< 9; i++){
                    sixball.ball[i].setPower(power);
                    sixball.ball[i].setProPower(unitVec);
                }
            }
            break;

  		default:
		//glutIdleFunc(0);
    		break;
		}
}



void init(void)
{
    ballObj1.setForm(0.5f,16.0f,16.0f);
    ballObj1.setPosition(7.5,0.0,7.5);
	glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_FRONT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, colorObject.white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, colorObject.white);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  init();
  glutMainLoop();
  return 0;
}
