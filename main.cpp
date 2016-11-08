#include <GL/glut.h>
#include <stdio.h>

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void resize(int w, int h){

	/* ウィンドウ全体をビューポートにする */
	glViewport(0, 0, w, h);
	/* 変換行列の初期化 */
	glLoadIdentity();

	/*Screen上の座標系をマウスの座標系に一致させる*/
	glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h -0.5, -0.5, -1.0, 1.0);
}

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

void mouse(int button, int state, int x, int y){
	static int x0, y0;
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_UP){
				/* ボタンを押した位置から離した位置まで線を引く */
		        glColor3d(0.0, 0.0, 0.0);
		        glBegin(GL_LINES);
		        glVertex2i(x0, y0);
		        glVertex2i(x, y);
		        glEnd();
		        glFlush();

			}
			else{
				/*ボタンを押した位置を覚える*/
				x0 = x;
				y0 = y;
			}
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		default:
			break;
		}
	}

int main(int argc, char *argv[]){
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 240);
	glutInit(&argc, argv);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
	return 0;
}
