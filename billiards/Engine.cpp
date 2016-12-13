#include <GLUT/GLUT.h>
#include <math.h>
class Engine{
public:
    static void UnitVector(GLfloat point1[],GLfloat point2[], GLfloat *p){
        GLfloat pp[] = { (float)(point1[0] - point2[0]), (float)(point1[1] - point2[1]), (float)(point1[2] - point2[2]) };
        float a = sqrt(pp[0]*pp[0]+pp[1]*pp[1]+pp[2]*pp[2]);
        GLfloat pp2[] = { (float)(pp[0]/a),pp[1]/a,(float)(pp[2]/a)};
        *p = pp2[0];
        ++p;
        *p = pp2[1];
        ++p;
        *p = pp2[2];
    }
    static double pow(double p){
        p = p * p;
        return p;
    }
    
    
    //ベクトルの分散のときに利用
    static void Disassembly(float ball_vec_X,float ball_vec_Y,float opponet_your_Angle, GLfloat a[]){
        //２つの速度の合成:OK
        double speedV_mix = sqrt((ball_vec_X * ball_vec_X) + (ball_vec_Y * ball_vec_Y));
        //球の進行方向:OK
        double myBallDirection = atan2(ball_vec_Y, ball_vec_X);
        //衝突後相手球の進行方向」に対する「自球衝突前進行方向」の角度の差:OK
        double Angle_differens = myBallDirection - opponet_your_Angle;
        //衝突後の相手の弾の速度:OK
        float speedV1 = fabs(speedV_mix * cos(Angle_differens));
        //衝突後の自分の弾の速度:OK
        float speedV2 = fabs(speedV_mix * sin(Angle_differens));
        //衝突後の相手の球のX速度:OK
        float opponentSpeedVx = -speedV1*cos(opponet_your_Angle);
        //Y速度:OK
        float opponentSpeedVy = -speedV1*sin(opponet_your_Angle);
        float Uxs;
        float Uys;
        //自分の弾の速度
        if(sin(Angle_differens) < 0){
            Uxs = speedV2 * cos(opponet_your_Angle - M_PI/2);//衝突後の自球のx速度
            Uys = speedV2 * sin(opponet_your_Angle - M_PI/2);//衝突後の自球のy速度
        } else{
            Uxs = speedV2 * cos(opponet_your_Angle + M_PI/2);//衝突後の自球のx速度
            Uys = speedV2 * sin(opponet_your_Angle + M_PI/2);//衝突後の自球のy速度
        }
        
        a[0] = Uxs;
        a[1] = Uys;
        a[2] = opponentSpeedVx;
        a[3] = opponentSpeedVy;
    }
};
