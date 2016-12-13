//#include "head/Label2D.h"
//#include "Engine.cpp"
//#include "GameManager.cpp"
////衝突判定
//
//void hitJudgment(NineBall nineballObj, int i, int j){
//    float x1 = nineballObj.ball[i].position->x;
//    float y1 = nineballObj.ball[i].position->y;
//    float z1 = nineballObj.ball[i].position->z;
//    
//    float x2 = nineballObj.ball[j].position->x;
//    float y2 = nineballObj.ball[j].position->y;
//    float z2 = nineballObj.ball[j].position->z;
//    
//    
//    
//    //当たり判定
//    if(Engine::pow(x1 - x2) + Engine::pow(y1 - y2) + Engine::pow(z1 - z2) <= Engine::pow(nineballObj.ball[i].width + nineballObj.ball[j].width)){
//        
//        if(nineballObj.ball[i].getId() == 0 && nineballObj.ball[i].is_move){
//            printf("はいった");
//            if(firstCollision != nineballObj.ball[j].getId()){
//                printf("FAL");
//                //フォルスだったとき！！
//                GameManager::setPlayerOperationState_Miss(PlayerOperationState_Miss::FAL);
//                combo = 0;
//            }
//            else{
//                combo += 2;
//                printf("GOOD%i",nineballObj.ball[i].getId());
//                printf("GOOD%i",firstCollision);
//                printf("SUCCESS\n");
//                GameManager::setPlayerOperationState_Miss(PlayerOperationState_Miss::GOOD);
//            }
//        }
//        
//        //分解中身
//        double kaku0 = atan2((z1 - z2),(x1 - x2));
//        double kaku00 = atan2((z2 - z1),(x2 - x1));
//        GLfloat tmpHoge[] ={0.0f,0.0f,0.0f,0.0f};
//        GLfloat tmpHoge2[] ={0.0f,0.0f,0.0f,0.0f};
//        
//        Engine::Disassembly(nineballObj.ball[i].getVector_x(), nineballObj.ball[i].getVector_z() , kaku0, tmpHoge);
//        Engine::Disassembly(nineballObj.ball[j].getVector_x(), nineballObj.ball[j].getVector_z() , kaku00, tmpHoge2);
//        
//        //結果の合成
//        GLfloat tmpHoge3[] ={
//            tmpHoge[0]+tmpHoge2[2],
//            tmpHoge[1]+tmpHoge2[3],
//            tmpHoge[2]+tmpHoge2[0],
//            tmpHoge[3]+tmpHoge2[1]
//        };
//        
//        //ベクトルのセットって言うか更新
//        nineballObj.ball[i].setPositionPro(tmpHoge3[0],0.0f,tmpHoge3[1]);
//        nineballObj.ball[i].setPosition();
//        nineballObj.ball[j].setPositionPro(tmpHoge3[2],0.0f,tmpHoge3[3]);
//        nineballObj.ball[j].setPosition();
//    }
//}
//
//
////2Dディスプレイ西洋Object作っていいかも
//void display2D(std::string str, double x, double y){
//    glRasterPos2f(x, y);
//    int size = (int)str.size();
//    for(int i = 0; i < size; ++i){
//        char ic = str[i];
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ic);
//    }
//}
//
//void display2D(std::string str, double x, double y,double z){
//    // WAIT
//    glRasterPos3d(x, y, z);
//    int size = (int)str.size();
//    for(int i = 0; i < size; ++i){
//        char ic = str[i];
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ic);
//    }
//}
//
//
//
//void create2DLabel(NineBall nineball){
//    std::string str;
//    //玉の上に玉の番号を表示してあげます
//    for(int i = 0; i < ballNum; i++){
//        if(nineball.ball[i].is_Existence){
//            //glPushMatrixとglPopMatrixはニコイチなのでインデントを下げます
//            glPushMatrix();
//            str = std::to_string(nineball.ball[i].getId());
//            display2D(str,nineball.ball[i].getPosition_x(),1,nineball.ball[i].getPosition_z());
//            glPopMatrix();
//        }
//    }
//    
//    // 平行投影にする
//    glMatrixMode(GL_PROJECTION);
//    
//    glPushMatrix();
//    glLoadIdentity();
//    gluOrtho2D(1, 1, 1, 1);
//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
//    glLoadIdentity();
//    str = std::to_string(firstCollision);
//    
//    
//    //次に落とすべき玉
//    str = "NEXT:"+str;
//    display2D(str,0.5, 0.8);
//    
//    
//    // ゲームの結果
//    display2D(gameStateLabelMiss,0.0,0.0);
//    
//    // スコアを表示
//    str = std::to_string(score);
//    str = "score:"+str;
//    display2D(str,-0.9f, 0.8f);
//    
//    
//    display2D(powerLabel,-1,-0.8);
//    
//    glPopMatrix();
//    glMatrixMode(GL_PROJECTION);
//    
//    glPopMatrix();
//    glMatrixMode(GL_MODELVIEW);
//}
