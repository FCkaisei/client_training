#include <stdio.h>
#include <GLUT/GLUT.h>
#include <vector>
#include <cmath>
ColorObject col;
class LightObject{
public:

	void setPosition(GLfloat params[4]){
		pos[4] = params[4];
	}

	GLfloat getPosition(){
		return pos[4];
	}

	void lightfv(GLenum light, GLenum pname, GLfloat params[4]){
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, col.green);
		glLightfv(GL_LIGHT1, GL_SPECULAR, col.red);
		glLightfv(light, pname, params);
	}
private:
	GLfloat pos[4];
};
