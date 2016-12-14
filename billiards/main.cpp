#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <GLUT/GLUT.h>
#include <vector>
#include <cmath>
#include <math.h>

#include "Table.cpp"
#include "head/Nineball.h"
#include "Engine.cpp"
#include "GameManager.cpp"
#include "head/LightObject.h"
#include "head/CameraSetting.h"
#include "head/Vector.h"
#include "head/GameValue.h"
#include "head/Label2D.h"


NineBall nineball;
CameraSetting cameraObj;
LightObject light;
Table table;
Label2D label2d;
PlayerOperationState GameManager::p_OperationState;
PlayerOperationState_Miss GameManager::p_OperationStateMiss;

GLfloat p_position[] = { 0.0,0.0,0.0 };
GLfloat unitVec[] = { 0.0,0.0,0.0 };

float now_shot_power = 0.0f;
bool is_AllStop = false;
bool now_Button_e = false;
bool Re_noowShot_power = false;



void idle(void){
  glutPostRedisplay();
}

//ゲームのステートを変更します。
void gameState(){
    if(GameManager::getPlayerOperationState() == PlayerOperationState::WAIT){
        cameraObj.createView(*nineball.ball[0].position);
        GameManager::setPlayerOperationState_Miss(PlayerOperationState_Miss::NONE);
    }else{
        GLfloat cameraPosition[] = {20.0,80.0,0.0};
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
    if(GameManager::getPlayerOperationState_Miss() == PlayerOperationState_Miss::CLEAR){
        gameStateLabelMiss = "CLEAR";
        //ここでナインボールを再度生成。　もしくは値をもとに戻して初期値に戻す
        nineball.ResetAll();
    }
}

//テーブル作成
void createTable(){
    table.SetTable();
    table.CreateTable();
}

//球同士の衝突判定
void hitJudgment(int i, int j){
    
    if(i == j){
        return;
    }
    float myBall_x = nineball.ball[i].position->x;
    float myBall_y = nineball.ball[i].position->y;
    float myBall_z = nineball.ball[i].position->z;
    
    float otherBall_x = nineball.ball[j].position->x;
    float otherBall_y = nineball.ball[j].position->y;
    float otherBall_z = nineball.ball[j].position->z;
    
    //当たり判定
    if(Engine::pow(myBall_x - otherBall_x) + Engine::pow(myBall_y - otherBall_y) + Engine::pow(myBall_z - otherBall_z) <= Engine::pow(nineball.ball[i].width + nineball.ball[j].width)){
        if(nineball.ball[i].getId() == 0 && nineball.ball[i].is_move){
            if(firstCollision != nineball.ball[j].getId()){
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
        //分解中身
        double my_angleDiff = atan2((myBall_z - otherBall_z),(myBall_x - otherBall_x));
        double Other_angleDiff = atan2((otherBall_z - myBall_z),(otherBall_x - myBall_x));
        
        
        GLfloat tmpVec1[] ={0.0f,0.0f,0.0f,0.0f};
        GLfloat tmpVec2[] ={0.0f,0.0f,0.0f,0.0f};
        
        //３番めが角度？？
        Engine::Disassembly(nineball.ball[i].getVector_x(), nineball.ball[i].getVector_z() , my_angleDiff, tmpVec1);
        Engine::Disassembly(nineball.ball[j].getVector_x(), nineball.ball[j].getVector_z() , Other_angleDiff, tmpVec2);
        
        //結果の合成
        GLfloat tmpVec3[] ={
            tmpVec1[0]+tmpVec2[2],
            tmpVec1[1]+tmpVec2[3],
            tmpVec1[2]+tmpVec2[0],
            tmpVec1[3]+tmpVec2[1]
        };
        
        //ベクトルのセットって言うか更新
        nineball.ball[i].setVector(tmpVec3[0],0.0f,tmpVec3[1]);
        nineball.ball[j].setVector(tmpVec3[2],0.0f,tmpVec3[3]);
        nineball.ball[j].movePosition();
    }
}


//9つのボールを生成します
void createNineBall(void){
    for(int i = 0; i < ballNum; i++){
        //自玉の時は別途処理を追加
        if(i == 0){
            for(int j = ballNum; j>0; j--){
                
                //はじめに当たることが許されている玉
                if(nineball.ball[j].is_Existence){
                    firstCollision = nineball.ball[j].getId();
                }
            }
            
            GLfloat cameraPosition[] = {(float)(p_position[0]+rsin), 0.0, (float)(p_position[2]+rcos)};
            //単位ベクトルの取得
            Engine::UnitVector(p_position, cameraPosition, unitVec);
        }
        
        if(nineball.ball[i].is_Existence){
            glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
            glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
            glMaterialf(GL_FRONT, GL_SHININESS, material_shinness);
        	glMaterialfv(GL_FRONT, GL_DIFFUSE, nineball.ball[i].color);
            glPushMatrix();
        	//色決め
            nineball.ball[i].collisionPockets();
        	//壁当たり判定チェック
        	nineball.ball[i].collisionDetectionBox();
        
        	//弾の数だけ弾同士の当たり判定チェック
        	for(int j = i; j < ballNum; j++){
                if(nineball.ball[j].is_Existence){
                    hitJudgment(i,j);
                }
        	}
            
            nineball.ball[i].movePosition();
        	nineball.ball[i].Draw();
        	nineball.ball[i].Physics();
        	glPopMatrix();
        }
    }
}



GLfloat initColor[] = {0.0,0.0,0.0,0.0};
//2Dラベルを生成します。
void create2DLabel(){
    std::string str;
    //玉の上に玉の番号を表示してあげます
    for(int i = 0; i < ballNum; i++){
        if(nineball.ball[i].is_Existence){
            glMaterialfv(GL_FRONT,GL_EMISSION,nineball.ball[i].color);
            str = std::to_string(nineball.ball[i].getId());
            label2d.display2D(str,nineball.ball[i].getPosition_x(),1,nineball.ball[i].getPosition_z());
            glPopMatrix();
        }
    }
    glMatrixMode(GL_PROJECTION);
    
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(1, 1, 1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    //次に落とすべき玉
    str = std::to_string(firstCollision);
    str = "NEXT:"+str;
    label2d.display2D(str,0.5, 0.8);
    
    // ゲームの結果
    label2d.display2D(gameStateLabelMiss,0.0,0.0);
    
    // スコアを表示
    str = std::to_string(score);
    str = "score:"+str;
    label2d.display2D(str,-0.9f, 0.8f);
    
    // ショットパワーを表示
    label2d.display2D(powerLabel,-1,-0.8);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glMaterialfv(GL_FRONT,GL_EMISSION,initColor);
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
                ballAngle += 0.04f;
            }
			break;
		case 'w':
			glutIdleFunc(idle);
            if(GameManager::getPlayerOperationState() == PlayerOperationState::WAIT){
                ballAngle -= 0.04;
            }
			break;
		case 'e':
            if(!now_Button_e){
            	if(GameManager::getPlayerOperationState() == PlayerOperationState::WAIT){
                    now_Button_e = true;
            	}
            }
            else{
            	if(GameManager::getPlayerOperationState() == PlayerOperationState::WAIT){
                    GameManager::setPlayerOperationState(PlayerOperationState::SHOT);
                    
                    nineball.ball[0].setPower(now_shot_power/3);
                    nineball.ball[0].setVectorPower(unitVec);
                    firstCollision = 0;
                    now_Button_e = false;
                    powerLabel = "power:";
                    now_shot_power = 0;
                    Re_noowShot_power = false;
                    nineball.ball[0].is_move = true;
                }
            }
            break;
    }
}


void powerGaugeManager(){
    //パワーゲージ管理
    //オブジェクト化しよう
    if(now_Button_e){
        powerLabel = "power:";
        if(!Re_noowShot_power){
            now_shot_power += 0.5f;
            if(now_shot_power > 30){
                Re_noowShot_power = true;
            }
        }
        else{
            now_shot_power -= 0.5f;
            if(now_shot_power < 1.0f){
                Re_noowShot_power = false;
            }
        }
        for(float i = 0; i < now_shot_power; i++){
            powerLabel += "|";
        }
    }
}


//球全てがPocketに落ちている状況下を確認
void CheckGameClear(){
    //ゲームがClear状態化を確認しています
    bool clear = true;
    for(int i = 1; i<ballNum; i++){
        if(nineball.ball[i].is_Existence == true){
            clear = false;
        }
    }
    if(clear){
        GameManager::setPlayerOperationState_Miss(PlayerOperationState_Miss::CLEAR);
    }
}

//球全て止まっているかを確認
void CheckBallMoving(){
    int moveCount = 0;
    for(int i = 0; i < ballNum; i++){
        if(!nineball.ball[i].is_move){
            moveCount += 1;
            
        }
    }
    
    if(moveCount >=ballNum){
        
        GameManager::setPlayerOperationState(PlayerOperationState::WAIT);
        //自球がない状態の場合玉を再配置
        if(nineball.ball[0].is_Existence == false){
            nineball.ball[0].setPosition(10.0f,0.0f,10.0f);
            nineball.ball[0].is_Existence = true;
        }
    }
}

void init(void){
    //色を浄化、背景色を設定していないためこの入力が背景色となる
	glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_FRONT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}


/* 	一定間隔で実行される関数
 	ゲームの大きな処理はここで管理しています。
 */
void timer(int value) {
    
    //パワーゲージを管理
    powerGaugeManager();
    
    /* 正方形のサイズを増加 */
    glLoadIdentity();
    rcos = cos(ballAngle)*15;
    rsin = sin(ballAngle)*15;
    
    //ゲームがCLEAR状態か
    CheckGameClear();
    CheckBallMoving();
    
    //gameStateを管理する予定
    gameState();
    //Lightを生成
    light.createLight();
    
    //2D系のラベルを整理します
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

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
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
