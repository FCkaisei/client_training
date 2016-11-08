#include <GL/glut.h>

void display(void){

}

int main(int argc, char * argv[]){

	//環境初期化・引数の内容が初期化される
	glutInit(&argc, argv);
	//windowを開きます引数はwindowの名前になります
	glutCreateWindow(argv[0]);
	//引数funcは描画する関数へのポインタだよ　図形とかの表示で使うよ
	glutDisplayFunc(display);
	//無限ループこれによってイベント待ち状態になるよ
	glutMainLoop();
	return 0;
}
