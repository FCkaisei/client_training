#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <GLUT/GLUT.h>
#include <vector>
#include <cmath>
#include <math.h>

#include "ColorObject.cpp"
#include "Table.cpp"
#include "head/Nineball.h"
#include "KumaEngine.cpp"
#include "GameManager.cpp"
#include "head/LightObject.h"
#include "head/CameraSetting.h"
#include "head/Vector.h"
#include "head/GameValue.h"

NineBall nineball;
CameraSetting cameraObj;
LightObject light;
Table table;
ColorObject colorObject;
PlayerOperationState GameManager::p_OperationState;
PlayerOperationState_Miss GameManager::p_OperationStateMiss;


GLfloat p_position[] = { 0.0,0.0,0.0 };
GLfloat unitVec[] = { 0.0,0.0,0.0 };
bool moveBall = false;
int firstCollision = 0;
string gameStateLabel = "now loading...";
string gameStateLabelMiss = "--";
char nextQ = '0';


void idle(void){
  glutPostRedisplay();
}

//ゲームのステートを変更します。
void gameState(){
    //全ての弾が止まったらカメラモードを変更
    GLfloat ballVec[] = {0.0,0.0,0.0};
    nineball.ball[0].getVec(ballVec);
    
    if(nineball.ball[0].is_Existence == false){
        
        nineball.ball[0].setPositionPro(0.0f,0.0f,0.0f);
        nineball.ball[0].setPosition(4.0f,0.0f,4.0f);
        
        nineball.ball[0].is_Existence = true;
    }
    
    //球が止まっているとき
    if((ballVec[0] < 0.001 && ballVec[0] > -0.001)){
        moveBall = false;
        GameManager::setPlayerOperationState(PlayerOperationState::WAIT);
    }
    
    //球が止まってるとき
    if(GameManager::getPlayerOperationState() == PlayerOperationState::WAIT){
        
        gameStateLabel = "STOP";
        cameraObj.createView(*nineball.ball[0].position);
        GameManager::setPlayerOperationState_Miss(PlayerOperationState_Miss::NONE);
    }else{
        
        gameStateLabel = "MOVE";
        GLfloat cameraPosition[] = {0.0,80.0,0.0};
        cameraObj.createView(cameraPosition);
    }
    
    
    if(GameManager::getPlayerOperationState_Miss() == PlayerOperationState_Miss::FAL){
    	gameStateLabelMiss = "FALL";
    }
    else if(GameManager::getPlayerOperationState_Miss() == PlayerOperationState_Miss::NONE){
        gameStateLabelMiss = "";
    }
    else if(GameManager::getPlayerOperationState_Miss() == PlayerOperationState_Miss::GOOD){
        gameStateLabelMiss = "GOOD";
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
    
    
	//	ポケットを作る。（未完)
    for(int i = 0; i < 6; i++){
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_DIFFUSE, table.hall[i].color);
        table.hall[i].Draw();
        glPopMatrix();
    }
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
    
    if(i == j){
        return;
    }
    double power;
    double power2;
    nineball.ball[i].getPower(power);
    nineball.ball[j].getPower(power2);
    GLfloat p_form2[] = { 0.0,0.0,0.0 };
    nineball.ball[j].getForm(p_form2);
    float x = nineball.ball[i].position->x;
    float y = nineball.ball[i].position->y;
    float z = nineball.ball[i].position->z;
    //(x,z)
    //(x2,z2)
    
    float x2 = nineball.ball[j].position->x;
    float y2 = nineball.ball[j].position->y;
    float z2 = nineball.ball[j].position->z;

    
    //接点を0,0とする。
    
    
    //y=4x+4に垂直な直線はy=-1/4×x+bになります。
    
    //玉同士の直線の垂線
    
    
    //玉同士の接線
    
    
    
    //衝突判定
    if(pow(x - x2) + pow(y - y2) + pow(z - z2) <= pow(nineball.ball[i].width + nineball.ball[j].width)){
        if(moveBall && nineball.ball[i].getId() == 0){
            
            moveBall =false;
            if(firstCollision != nineball.ball[j].getId()){
                //フォルスだったとき！！
                GameManager::setPlayerOperationState_Miss(PlayerOperationState_Miss::FAL);
                
                combo = 0;
                
            }
            else{
                combo += 2;
                printf("GOOD%i",nineball.ball[i].getId());
                
                printf("GOOD%i",firstCollision);
                printf("SUCCESS\n");
                GameManager::setPlayerOperationState_Miss(PlayerOperationState_Miss::GOOD);
            }
        }
        
        
        
        //powerが強い側に従って玉移動
        if(power > power2){
            if(power > 0){
                collision(nineball.ball[i],nineball.ball[j]);
            }
        }
        else if(power < power2){
            if(power2 > 0){
                collision(nineball.ball[j],nineball.ball[i]);
            }
        }
        else if (power == power2){
            if(power > 0){
                collision(nineball.ball[i],nineball.ball[j]);
            }
        }
    }
}


//9つのボールを生成します
void  createNineBall(void){
    for(int i = 0; i < 9; i++){
        //自玉の時は別途処理を追加
        if(i == 0){
            for(int j = 9; j>0; j--){
                
                //はじめに当たることが許されている玉
                if(nineball.ball[j].is_Existence){
                    firstCollision = nineball.ball[j].getId();
                }
            }
            
            GLfloat cameraPosition[] = {(float)(p_position[0]+rsin), 0.0, (float)(p_position[2]+rcos)};
            
            //単位ベクトルの取得
            KumaEngine::UnitVector(p_position, cameraPosition, unitVec);
        }
        
        if(nineball.ball[i].is_Existence){
        
        	glPushMatrix();
        	//色決め
        	glMaterialfv(GL_FRONT, GL_DIFFUSE, nineball.ball[i].color);
        
            nineball.ball[i].collisionPockets();
        	//壁当たり判定チェック
        	nineball.ball[i].collisionDetectionBox();
        
        	//弾の数だけ弾同士の当たり判定チェック
        	for(int j = i; j < 9; j++){
                if(nineball.ball[j].is_Existence){
					hitJudgment(i,j);
                }
        	}
        	nineball.ball[i].setPosition();
        	nineball.ball[i].Draw();
        	nineball.ball[i].Physics();
        	glPopMatrix();
        }
    }
}

void display2D(string str, double x, double y){
    // WAIT
    glRasterPos2f(x, y);
    int size = (int)str.size();
    for(int i = 0; i < size; ++i){
        char ic = str[i];
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ic);
    }
}


void create2DLabel(){
    // 平行投影にする
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(1, 1, 1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    display2D(gameStateLabel, -0.9,0.9);
    
    std::string str = std::to_string(firstCollision);
    str = "NEXT:"+str;
    
    display2D(str,0.5, 0.8);
    
    // ゲームの結果
    display2D(gameStateLabelMiss,0.0,0.0);
    
    // スコアを表示
    str = std::to_string(score);
    str = "score:"+str;
    display2D(str,0.5f, -0.8f);
    
    // コンボ数
    str = std::to_string(combo);
    str = "magnification::"+str;
    display2D(str,-0.9,-0.8);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    
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
                ballAngle += 0.05f;
            }
			break;
		case 'w':
		glutIdleFunc(idle);
            if(GameManager::getPlayerOperationState() == PlayerOperationState::WAIT){
                ballAngle -= 0.05;
            }
			break;
		case 'e':
            if(GameManager::getPlayerOperationState() == PlayerOperationState::WAIT){
                GameManager::setPlayerOperationState(PlayerOperationState::SHOT);
                shotPower= 1.2f;
                nineball.ball[0].setPower(shotPower);
                nineball.ball[0].setVectorPower(unitVec);
                moveBall = true;
                firstCollision = 0;
            }
            break;

        case 'f':
            nineball.ball[1].is_Existence = false;
            break;
            
  		default:
    		break;
		}
}

//初期化
void init(void){
    nineball.ball[0].setForm(0.5f,16.0f,16.0f);
    nineball.ball[0].setPosition(7.5,0.0,7.5);
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
    rcos = cos(ballAngle)*15;
    rsin = sin(ballAngle)*15;
    
    //gameStateを管理する予定
    gameState();
    
    //Lightを生成
    light.createLight();
    
    create2DLabel();
    
    //土台生成
    createTable();
    
    //9ボールを生成します(当たり判定もしちゃってるで確認)
    createNineBall();
    
    //実際に描画します
    glFlush();
    
    //画面を再描写
    glutPostRedisplay();
    ///30ミリ秒後に再実行
    glutTimerFunc(30, timer, 0);
}

//メインスレッド
int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
  	glutDisplayFunc(display);
    //30ミリ秒後に timer() を実行
    glutTimerFunc(30, timer, 0);
    glutReshapeFunc(resize);
  	glutKeyboardFunc(key);
  	init();
  	glutMainLoop();
  	return 0;
}
