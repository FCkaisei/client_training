#include <stdio.h>
#include <GL/glut.h>

#define MAXPOINTS 100	//記憶する点の数
GLint point[MAXPOINTS][2]; //座標を記憶する配列
int pointnum = 0;	//記録した座標のカズ
void display(void){
	int i;
	//Colorバッファを指定して塗りつぶしますわよ
	glClear(GL_COLOR_BUFFER_BIT);

	if(pointnum > 1){
		glColor3d(0.0,0.0,0.0);
		glBegin(GL_LINES);
		for(i = 0; i < pointnum; ++i){
			glVertex2iv(point[i]);
		}
		glEnd();
	}

	//まだ実行されていない命令を実行する
	glFlush();
}

void resize(int w, int h){
	//ウィンドウ全体をビューポートにする
	//開いたウィンドウの中で実際の描画が行われる領域がビューポート
	glViewport(0, 0, w, h);
	//変換行列の初期化
	glLoadIdentity();
	//Screen上の表示領域をビューポートと比例させる。
	glOrtho(-0.5, (GLdouble)w -0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}

void mouse(int button, int state, int x, int y){
	switch(button){
		case GLUT_LEFT_BUTTON:
		point[pointnum][0] = x;
		point[pointnum][1] = y;
			if(state == GLUT_UP){
				glColor3d(0.0, 0.0, 0.0);
				glBegin(GL_LINES);
				glVertex2iv(point[pointnum -1]);
				glVertex2iv(point[pointnum]);
				glVertex2i(x0, y0);
				glVertex2i(x, y);
				glEnd();
				glFlush();
			}
			else{
			}
			if(pointnum < MAXPOINTS -1) ++pointnum;
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		default:
			break;
	}
}

//コンストラクタみたいな　一回しか呼ばれない
void init(void){
	//色の指定ですわよ
	glClearColor(1.0,1.0,1.0,1.0);
}

int main(int argc, char * argv[]){
	//windowの場所
	glutInitWindowPosition(100, 100);
	//windowのサイズ
	glutInitWindowSize(320, 240);

	//環境初期化・引数の内容が初期化される
	glutInit(&argc, argv);
	//ディスプレイの表示モード、主に色の指定.
	glutInitDisplayMode(GLUT_RGBA);
	//windowを開きます引数はwindowの名前になります
	glutCreateWindow(argv[0]);
	//引数funcは描画する関数へのポインタだよ　図形とかの表示で使うよ
	glutDisplayFunc(display);
	//windowがリサイズされたときに事項する関数ポインタを与える。
	glutReshapeFunc(resize);
	//マウスのボタンが押されたときに実行する関数ポインタ
	glutMouseFunc(mouse);
	//一回しか呼ばれない
	init();
	//無限ループこれによってイベント待ち状態になるよ
	glutMainLoop();
	return 0;
}
