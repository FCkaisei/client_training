#include <GL/glut.h>

void display(void){
	//Colorバッファを指定して塗りつぶしますわよ
	glClear(GL_COLOR_BUFFER_BIT);
	//まだ実行されていない命令を実行する
	glFlush();
}
//コンストラクタみたいな　一回しか呼ばれない
void init(void){
	//色の指定ですわよ
	glClearColor(0.0,0.0,1.0,1.0);
}

int main(int argc, char * argv[]){

	//環境初期化・引数の内容が初期化される
	glutInit(&argc, argv);
	//ディスプレイの表示モード、主に色の指定.
	glutInitDisplayMode(GLUT_RGBA);
	//windowを開きます引数はwindowの名前になります
	glutCreateWindow(argv[0]);
	//引数funcは描画する関数へのポインタだよ　図形とかの表示で使うよ
	glutDisplayFunc(display);
	//一回しか呼ばれない
	init();
	//無限ループこれによってイベント待ち状態になるよ
	glutMainLoop();
	return 0;
}
