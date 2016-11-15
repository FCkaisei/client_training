#include <stdio.h>
#include <iostream>
#include <string>
#include <GLUT/GLUT.h>
#include <vector>
#include <cmath>
#include <math.h>

#include "ColorObject.cpp"
#include "Table.cpp"
#include "NineBall.cpp"
#include "KumaEngine.cpp"
#include "GameManager.cpp"
#include "head/LightObject.h"
#include "head/CameraSetting.h"

CameraSetting cameraObj;
LightObject light;
Table table;
SixBall sixball;
ColorObject colorObject;
PlayerOperationState GameManager::p_OperationState;
GLfloat p_position[] = { 0.0,0.0,0.0 };
GLfloat unitVec[] = { 0.0,0.0,0.0 };


double r = 0; /* 回転角 */
double rcos;
double rsin;
double shotPower = 0;
GLdouble s = 0.5;

void idle(void){
  glutPostRedisplay();
}

//カメラの設定を行っています(玉が止まっているとき)
void createView(){
    gluLookAt(
              (float)p_position[0]+rsin, 3.0, (float)p_position[2]+rcos,
              (float)p_position[0], 0.0, (float)p_position[2],
              0.0, 1.0, 0.0);
}

//カメラの設定(弾が動いているとき)
void createView(GLfloat gl[]){
    gluLookAt(gl[0],gl[1],gl[2],
              15.0, 1.0, 7.5,
              0.0,3.0,0.0
    );
}

//ゲームのステートを変更します。
void gameState(){
    //全ての弾が止まったらカメラモードを変更
    GLfloat ballVec[] = {0.0,0.0,0.0};
    sixball.ball[0].getVec(ballVec);
    
    if((ballVec[0] < 0.001 && ballVec[0] > -0.001) || (ballVec[2] < 0.001 && ballVec[2] > -0.001)){
        GameManager::setPlayerOperationState(PlayerOperationState::WAIT);
    }
    
    if(GameManager::getPlayerOperationState() == PlayerOperationState::WAIT){
        cameraObj.createView(p_position,rsin,rcos);
    }
    else{
        GLfloat cameraPosition[] = {0.0,60.0,0.0};
        cameraObj.createView(cameraPosition);
    }
}


double pow(double p){
    p = p*p;
    return p;
}


//土台の生成
void createTable(){
    table.SetTable();
    
    //土台を作る
    for(int i = 0; i < 7; i++){
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_DIFFUSE, table.box[i].color);
        table.box[i].Draw();
        glPopMatrix();
    }
    
	//ポケットを作る。（未完)
//    for(int i = 0; i < 6; i++){
//        glPushMatrix();
//        glMaterialfv(GL_FRONT, GL_DIFFUSE, table.hall[i].color);
//        table.hall[i].Draw();
//        glPopMatrix();
//    }
}


//衝突時の値変動
void collision(BallObject &ballObj,BallObject &ballObj2){
    
    GLfloat formerBallVector[3] = {-ballObj.vector[0], ballObj.vector[1], -ballObj.vector[2]};
    ballObj.setVectorPower(formerBallVector);
    GLfloat supplierBallVector[3] = {-ballObj.vector[0], ballObj.vector[1], -ballObj.vector[2]};
    
    //衝突先のたまにベクトルを渡す
    double power;
    ballObj.getPower(power);
    ballObj2.setPower(power);
    ballObj2.setVectorPower(supplierBallVector);
}


//衝突判定
void hitJudgment(int i, int j){
    if(i != j){
        double power;
        double power2;
        sixball.ball[i].getPower(power);
        sixball.ball[j].getPower(power2);
        GLfloat p_position2[] = { 0.0,0.0,0.0 };
        GLfloat p_form2[] = { 0.0,0.0,0.0 };
        sixball.ball[j].getPosition(p_position2);
        sixball.ball[j].getForm(p_form2);
        
        //衝突判定
        if(pow(sixball.ball[i].positionX - p_position2[0]) + pow(sixball.ball[i].positionY - p_position2[1]) + pow(sixball.ball[i].positionZ - p_position2[2]) <= pow(sixball.ball[i].width + p_form2[0])){
            
            //powerが強い側に従って玉移動
            if(power > power2){
        		if(power > 0){
               	 	collision(sixball.ball[i],sixball.ball[j]);
                    printf("%s","Win");
            	}
        	}
        	else if(power < power2){
        		if(power2 > 0){
                    printf("%s","Lose");
            		collision(sixball.ball[j],sixball.ball[i]);
            	}
        	}
            else if (power == power2){
				if(power > 0){
                    printf("%s","Draw");
                    collision(sixball.ball[i],sixball.ball[j]);
                }
            }
        }
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
        
        //弾の数だけ弾同士の当たり判定チェック
        for(int j = i; j < 9; j++){
			hitJudgment(i,j);
        }
        sixball.ball[i].setPosition();
        sixball.ball[i].Draw();
        sixball.ball[i].Physics();
        glPopMatrix();
    }
}


//再描写時に実行される関数
void display(void){
    //特定の色で指定バッファを削除する
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


//ウィンドウの比率の固定などに利用
void resize(int w, int h){
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
                shotPower = 1.2f;
                sixball.ball[0].setPower(shotPower);
                sixball.ball[0].setVectorPower(unitVec);
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

/* 100ミリ秒ごとに実行される関数 */
void timer(int value) {
    /* 正方形のサイズを増加 */
    glLoadIdentity();
    rcos = cos(r)*15;
    rsin = sin(r)*15;
    sixball.ball[0].getPosition(p_position);
    //gameStateを管理する予定
    gameState();
    //Lightを生成
    
    light.createLight();
    //土台生成
    createTable();
    //9ボールを生成します(当たり判定もしちゃってるで確認)
    createNineBall();
    //実際に描画します
    glFlush();
    /* 画面を再描写 */
    glutPostRedisplay();
    /* 100ミリ秒後に再実行 */
    glutTimerFunc(30, timer, 0);
}

//メインスレッド
int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
  	glutDisplayFunc(display);
    /* 100ミリ秒後に timer() を実行 */
    glutTimerFunc(30, timer, 0);
    glutReshapeFunc(resize);
  	glutKeyboardFunc(key);
  	init();
  	glutMainLoop();
  	return 0;
}
