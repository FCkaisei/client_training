#include <stdio.h>
#include <GL/glut.h>

void display(void){
	//Colorバッファを指定して塗りつぶしますわよ
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1.0, 0.0,0.0);
	//図形を書くときに用意する関数ですわよ、関数に描画する図形タイプを設定する
	glBegin(GL_POLYGON);
	//二次元の座標値の設定ですのよ
	glVertex2d(-0.9, -0.9);
	glColor3d(0.0, 1.0, 0.0); /* 緑 */
	glVertex2d(0.9, -0.9);
	glVertex2d(0.9, 0.9);
	glVertex2d(-0.9, 0.9);
	glEnd();

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
	glOrtho(-w / 200, w / 200.0, -h / 200.0, h/ 200.0, -1.0, 1.0);
}

void mouse(int button, int state, int x, int y){
	switch(button){
		case GLUT_LEFT_BUTTON:
			printf("left");
			break;
		case GLUT_MIDDLE_BUTTON:
			printf("middle");
			break;
		case GLUT_RIGHT_BUTTON:
			printf("right");
			break;
		default:
			break;
	}

	printf("button is");

	switch(state){
		case GLUT_UP:
			printf("UP");
			break;
		case GLUT_DOWN:
			printf("down");
			break;
		default:
			break;
	}

	printf(" at (%d,%d)\n",x,y);
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
