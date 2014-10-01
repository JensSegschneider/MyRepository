// C++.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <GL/glut.h>

void render(void);
void reshape(int w, int h);

int wi = 500;
int he = 250;
float ratio;

int main(int argc, char **argv)
{
	ratio = wi/he;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	
	glutInitWindowPosition(100,100);
	glutInitWindowSize(wi,he);
	glutCreateWindow("OpenGL");
	
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}

void render(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glBegin(GL_POLYGON);
		glVertex2f(0.0,-0.5);
		glVertex2f(-0.5,-0.3);
		glVertex2f(-0.5,0.3);
		glVertex2f(0.0,0.5);
		glVertex2f(0.5,0.3);
		glVertex2f(0.5,-0.3);
	glEnd();

	glutSwapBuffers();
}

void reshape(int w, int h)
{

	float acspectratio;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w > h){
		acspectratio = w/(float)h;
		gluOrtho2D(-acspectratio,acspectratio,-1,1);
	} else {
		acspectratio = h/(float)w;
		gluOrtho2D(-1,1,-acspectratio,acspectratio);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0,w,h);
}
