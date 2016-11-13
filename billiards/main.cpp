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
ColorObject colorObject;
PlayerOperationState GameManager::p_OperationState;
GLfloat p_position[] = { 0.0,0.0,0.0 };
GLfloat unitVec[] = { 0.0,0.0,0.0 };
double r = 0; /* 回転角 */
double rcos;
double rsin;
double power = 0;

void idle(void){
  glutPostRedisplay();
}

//カメラの設定を行っています
void createView(){
    gluLookAt(
              (float)p_position[0]+rsin, 3.0, (float)p_position[2]+rcos,
              (float)p_position[0], 0.0, (float)p_position[2],
              0.0, 1.0, 0.0);
}

//カメラの設定
void createView(GLfloat gl[]){
    gluLookAt(gl[0],gl[1],gl[2],
              15.0, 1.0, 7.5,
              0.0,3.0,0.0
    );
}

//ゲームのステートを変更します。
void gameState(){
    //ここはステート処理にしたい。だから外部にカメラをステートで管理するクラスをセットしようね。
    //全ての弾が止まったらカメラモードを変更　っていうか、弾が止まる操作不能にする必要がある
    GLfloat hoge2[] = {0.0,1.0,0.0};
    sixball.ball[0].getVec(hoge2);
    
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
}

//Lightの設定
void createLight(){
    /* 光源の位置設定 */
    GLfloat light0pos[] = { 0.0, 3.0, 5.0, 1.0 };
    GLfloat light1pos[] = { 5.0, 3.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
    
}

double pow(double p){
    p = p*p;
    return p;
}

//土台の作成
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
    
}

//9つのボールを生成します
void  createNineBall(void){
    for(int i = 0; i < 9; i++){
        if(i == 0){
            GLfloat cameraPosition[] = {(float)(p_position[0]+rsin), 0.0, (float)(p_position[2]+rcos)};
            //単位ベクトルの取得
            KumaEngine::UnitVector(p_position, cameraPosition, unitVec);
        }
        
        glPushMatrix();
        
        //色決め
        glMaterialfv(GL_FRONT, GL_DIFFUSE, sixball.ball[i].color);
        
        //壁当たり判定チェック
        sixball.ball[i].collisionDetectionBox();
        
        //弾の数だけ弾通しの当たり判定チェック
        for(int j = 0; j < 9; j++){
            if(i == 0){
            	if(i != j){
                    GLfloat p_position2[] = { 0.0,0.0,0.0 };
                    GLfloat p_form2[] = { 0.0,0.0,0.0 };
                    sixball.ball[j].getPosition(p_position2);
                    sixball.ball[j].getForm(p_form2);
                    
                    if(pow(sixball.ball[i].positionX - p_position2[0])+
                       pow(sixball.ball[i].positionY - p_position2[1])+
                       pow(sixball.ball[i].positionZ - p_position2[2]) <= pow(sixball.ball[i].width + p_form2[0])){

                        printf("%s","衝突");
                        GLfloat u[3] = {-sixball.ball[i].vector[0], sixball.ball[i].vector[1], -sixball.ball[i].vector[2]};
                        sixball.ball[i].setProPower(u);
                        GLfloat u2[3] = {-sixball.ball[i].vector[0], sixball.ball[i].vector[1], -sixball.ball[i].vector[2]};
                        
                        sixball.ball[j].power = sixball.ball[i].power;
                        sixball.ball[j].setProPower(u2);
                    }
            	}
            }
        }
        
        //ポジションをセットする
        sixball.ball[i].setPosition();
        
        //描画
        sixball.ball[i].Draw();
        sixball.ball[i].Physics();
        glPopMatrix();
    }
}

//再描写時に実行される関数
void display(void){
    //特定の色で指定バッファを削除する
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    rcos = cos(r)*15;
    rsin = sin(r)*15;
    sixball.ball[0].getPosition(p_position);
    
    //gameStateを管理する予定
    gameState();
	
    //Lightを生成
    createLight();
    
    //土台生成
    createObj();
    
    //9ボールを生成します
    createNineBall();
    
	//実際に描画します
    glFlush();
    
    
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


//キーボード入力を管理
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
                for(int i = 0; i < 1; i++){
                	sixball.ball[i].setPower(power);
                	sixball.ball[i].setProPower(unitVec);
                }
            }
            break;

  		default:
    		break;
		}
}


//初期化
void init(void){
    sixball.ball[0].setForm(0.5f,16.0f,16.0f);
    sixball.ball[0].setPosition(7.5,0.0,7.5);
	glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_FRONT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, colorObject.white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, colorObject.white);
}

//メインスレッド
int main(int argc, char *argv[]){
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
