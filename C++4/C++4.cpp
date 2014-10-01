// C++4.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <GL\glut.h>

#define winposx 100
#define winposy 100
#define winsizex 500
#define winsizey 500

double posy=0; 
double posx=0;

void render(void);
void addCone();
void addCone2();
void specialKeys( int key, int x, int y );

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(winposx,winposy);
	glutInitWindowSize(winsizex,winsizey);
	glutCreateWindow("OpenGL");
	glutDisplayFunc(render);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}

void render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float pos[]={posx,posy,-3.0,1.0};
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	glLoadIdentity();
	glRotatef( -50, 1.0, 0.0, 0.0 );
	glTranslated(0.4,0,0);
	addCone();
	glTranslated(-0.8,0,0);
	addCone2();
	glutSwapBuffers();
}

void addCone(){
	GLUquadricObj *obj = gluNewQuadric();
 
	glBegin(GL_POLYGON);
		glNormal3f(0.0,0.0,1.0);
		gluCylinder(obj,0.2,0,1,2000,2000);
		float mat[4];
		mat[0] = 0.329412;
		mat[1] = 0.223529;
		mat[2] = 0.027451;
		mat[3] = 1.0;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
		mat[0] = 0.780392;
		mat[1] = 0.568627;
		mat[2] = 0.113725;
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
		mat[0] = 0.992157;
		mat[1] = 0.941176;
		mat[2] = 0.807843;
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,0.21794872 * 128);
	glEnd();
}

void addCone2(){
	GLUquadricObj *obj = gluNewQuadric();
 
	glBegin(GL_POLYGON);
		glNormal3f(0.0,0.0,1.0);
		gluCylinder(obj,0.2,0,1,2000,2000);
		float mat[4];
		mat[0] = 0.0;
		mat[1] = 0.0;
		mat[2] = 0.0;
		mat[3] = 1.0;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
		mat[0] = 0.5;
		mat[1] = 0.0;
		mat[2] = 0.0;
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
		mat[0] =  0.7;
		mat[1] =  0.6;
		mat[2] =  0.6;
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,0.25 * 128);
	glEnd();
}

void specialKeys( int key, int x, int y ) {
 
  if (key == GLUT_KEY_RIGHT)
    posx += 5;
  else if (key == GLUT_KEY_LEFT)
    posx -= 5;
 
  else if (key == GLUT_KEY_UP)
    posy += 5;
 
  else if (key == GLUT_KEY_DOWN)
    posy -= 5;
  glutPostRedisplay();
}