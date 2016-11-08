#include <stdio.h>
#include <GL/glut.h>

GLfloat light0pos[] = { 0.0, 3.0, 5.0, 1.0 };
GLfloat light1pos[] = { 5.0, 3.0, 0.0, 1.0 };

GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };

GLdouble vertex[][3] = {
  { 0.0, 0.0, 0.0 }, /* A */
  { 1.0, 0.0, 0.0 }, /* B */
  { 1.0, 1.0, 0.0 }, /* C */
  { 0.0, 1.0, 0.0 }, /* D */
  { 0.0, 0.0, 1.0 }, /* E */
  { 1.0, 0.0, 1.0 }, /* F */
  { 1.0, 1.0, 1.0 }, /* G */
  { 0.0, 1.0, 1.0 }  /* H */
};

int face[][4] = {
	{ 0, 1, 2, 3 },
	{ 1, 5, 6, 2 },
	{ 5, 4, 7, 6 },
	{ 4, 0, 3, 7 },
	{ 4, 5, 1, 0 },
	{ 3, 2, 6, 7 }
};

GLdouble color[][3] = {
  { 1.0, 0.0, 0.0 },
  { 0.0, 1.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  { 1.0, 1.0, 0.0 },
  { 1.0, 0.0, 1.0 },
  { 0.0, 1.0, 1.0 }
};

GLdouble normal[][3] = {
  { 0.0, 0.0,-1.0 },
  { 1.0, 0.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  {-1.0, 0.0, 0.0 },
  { 0.0,-1.0, 0.0 },
  { 0.0, 1.0, 0.0 }
};

void idle(void)
{
  glutPostRedisplay();
}


void display(void){
	int i;
	int j;
	static int r = 0; /* 回転角 */
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	/* 視点位置と視線方向 */
	gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


	/* 光源の位置設定 */
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

	/* 図形の回転 */
	glRotated((double)r, 0.0, 1.0, 0.0);

	/* 図形の色 (赤)  */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);

	glColor3d(0.0,0.0,0.0);
	glBegin(GL_QUADS);
	for(j = 0; j < 6; ++j){
		glColor3dv(color[j]);
		for(i = 0; i < 4; ++i){
			glVertex3dv(vertex[face[j][i]]);
		}
	}
  glEnd();

  glFlush();
  /* 一周回ったら回転角を 0 に戻す */
  if (++r >= 360) r = 0;
}

void resize(int w, int h){
	glViewport(0,0,w,h);

	/* 透視変換行列の設定 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
	/* モデルビュー変換行列の設定 */
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
  switch (button) {
  case GLUT_LEFT_BUTTON:
    if (state == GLUT_DOWN) {
      /* アニメーション開始 */
      glutIdleFunc(idle);
    }
    else {
      /* アニメーション停止 */
      glutIdleFunc(0);
    }
    break;
  case GLUT_RIGHT_BUTTON:
    if (state == GLUT_DOWN) {
      /* コマ送り (1ステップだけ進める) */
        glutPostRedisplay();
    }
    break;
  default:
    break;
  }
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
  case 'Q':
  case '\033':  /* '\033' は ESC の ASCII コード */
  //exit(0);
  default:
    break;
  }
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
    glLightfv(GL_LIGHT1, GL_SPECULAR, green);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
 glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();
  return 0;
}
