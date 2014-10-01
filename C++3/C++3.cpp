// C++3.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <GL\glut.h>

#define winposx 100
#define winposy 100
#define winsizex 500
#define winsizey 500
#define cuberposdown -0.1
#define cuberposup 0.1
#define cuberposfront 0.1
#define cuberposback -0.1
#define cubeposleft -0.4
#define cubeposright -0.2

void render(void);
void addQuad();
void addQuad2();
void addtethrahedron();


int main(int argc, char **argv)
{
	int menu;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(winposx,winposy);
	glutInitWindowSize(winsizex,winsizey);
	glutCreateWindow("OpenGL");
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}

void render(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef( 30, 1.0, 0.0, 0.0 );
	glRotatef( 120, 0.0, 1.0, 0.0 );
	glTranslated(0,0,-0.4);
	addQuad();
	glTranslated(0,0,0.4);
	addtethrahedron();
	glTranslated(0,0,0.4);
	addQuad2();
	glutSwapBuffers();
}

void addQuad(){
	//front
	glBegin(GL_LINES);
		glVertex3f(cubeposleft,cuberposdown,cuberposfront);
		glVertex3f(cubeposright,cuberposdown, cuberposfront);
		glVertex3f(cubeposright,cuberposup, cuberposfront);
		glVertex3f(cubeposleft,cuberposup, cuberposfront);
	glEnd();

	//back
	glBegin(GL_LINES);
		glVertex3f(cubeposleft,cuberposdown,cuberposback);
		glVertex3f(cubeposright,cuberposdown, cuberposback);
		glVertex3f(cubeposright,cuberposup, cuberposback);
		glVertex3f(cubeposleft,cuberposup, cuberposback);
	glEnd();

	//right
	glBegin(GL_LINES);
		glVertex3f(cubeposright,cuberposdown,cuberposback);
		glVertex3f(cubeposright,cuberposup, cuberposback);
		glVertex3f(cubeposright,cuberposup, cuberposfront);
		glVertex3f(cubeposright,cuberposdown, cuberposfront);
	glEnd();

	//left
	glBegin(GL_LINES);
		glVertex3f(cubeposleft,cuberposdown,cuberposback);
		glVertex3f(cubeposleft,cuberposup, cuberposback);
		glVertex3f(cubeposleft,cuberposup, cuberposfront);
		glVertex3f(cubeposleft,cuberposdown, cuberposfront);
	glEnd();

	//up
	glBegin(GL_LINES);
		glVertex3f(cubeposleft,cuberposup,cuberposback);
		glVertex3f(cubeposleft,cuberposup, cuberposfront);
		glVertex3f(cubeposright,cuberposup, cuberposfront);
		glVertex3f(cubeposright,cuberposup, cuberposback);
	glEnd();

	//down
	glBegin(GL_LINES);
		glVertex3f(cubeposleft,cuberposdown,cuberposback);
		glVertex3f(cubeposleft,cuberposdown, cuberposfront);
		glVertex3f(cubeposright,cuberposdown, cuberposfront);
		glVertex3f(cubeposright,cuberposdown, cuberposback);
	glEnd();
}

void addtethrahedron(){
	//front
	glBegin(GL_LINE_LOOP);
		glVertex3f(cubeposleft,cuberposdown,cuberposfront);
		glVertex3f(cubeposright,cuberposdown, cuberposfront);
		glVertex3f((cubeposleft + cubeposright) / 2,cuberposup * 2, (cuberposfront + cuberposback) / 2);
	glEnd();

	//right
	glBegin(GL_LINE_LOOP);
		glVertex3f(cubeposright,cuberposdown, cuberposfront);
		glVertex3f(cubeposright,cuberposdown, cuberposback);
		glVertex3f((cubeposleft + cubeposright) / 2,cuberposup * 2, (cuberposfront + cuberposback) / 2);
	glEnd();

	//left
	glBegin(GL_LINE_LOOP);
		glVertex3f(cubeposleft,cuberposdown, cuberposfront);
		glVertex3f(cubeposright,cuberposdown, cuberposback);
		glVertex3f((cubeposleft + cubeposright) / 2,cuberposup * 2, (cuberposfront + cuberposback) / 2);
	glEnd();
}

void addQuad2(){
	//front
	glBegin(GL_LINES);
		glVertex3f(cubeposleft + (cubeposleft - cubeposright) / 2,cuberposdown,cuberposfront);
		glVertex3f(cubeposright - (cubeposleft - cubeposright) / 2,cuberposdown, cuberposfront);
		glVertex3f(cubeposright - (cubeposleft - cubeposright) / 2,cuberposup, cuberposfront);
		glVertex3f(cubeposleft + (cubeposleft - cubeposright) / 2,cuberposup, cuberposfront);
	glEnd();

	//back
	glBegin(GL_LINES);
		glVertex3f(cubeposleft + (cubeposleft - cubeposright) / 2,cuberposdown,cuberposback);
		glVertex3f(cubeposright - (cubeposleft - cubeposright) / 2,cuberposdown, cuberposback);
		glVertex3f(cubeposright - (cubeposleft - cubeposright) / 2,cuberposup, cuberposback);
		glVertex3f(cubeposleft + (cubeposleft - cubeposright) / 2,cuberposup, cuberposback);
	glEnd();

	//right
	glBegin(GL_LINES);
		glVertex3f(cubeposright - (cubeposleft - cubeposright) / 2,cuberposdown,cuberposback);
		glVertex3f(cubeposright - (cubeposleft - cubeposright) / 2,cuberposup, cuberposback);
		glVertex3f(cubeposright - (cubeposleft - cubeposright) / 2,cuberposup, cuberposfront);
		glVertex3f(cubeposright - (cubeposleft - cubeposright) / 2,cuberposdown, cuberposfront);
	glEnd();

	//left
	glBegin(GL_LINES);
		glVertex3f(cubeposleft + (cubeposleft - cubeposright) / 2,cuberposdown,cuberposback);
		glVertex3f(cubeposleft + (cubeposleft - cubeposright) / 2,cuberposup, cuberposback);
		glVertex3f(cubeposleft + (cubeposleft - cubeposright) / 2,cuberposup, cuberposfront);
		glVertex3f(cubeposleft + (cubeposleft - cubeposright) / 2,cuberposdown, cuberposfront);
	glEnd();

	//up
	glBegin(GL_LINES);
		glVertex3f(cubeposleft + (cubeposleft - cubeposright) / 2,cuberposup,cuberposback);
		glVertex3f(cubeposleft + (cubeposleft - cubeposright) / 2,cuberposup, cuberposfront);
		glVertex3f(cubeposright - (cubeposleft - cubeposright) / 2,cuberposup, cuberposfront);
		glVertex3f(cubeposright - (cubeposleft - cubeposright) / 2,cuberposup, cuberposback);
	glEnd();

	//down
	glBegin(GL_LINES);
		glVertex3f(cubeposleft + (cubeposleft - cubeposright) / 2,cuberposdown,cuberposback);
		glVertex3f(cubeposleft + (cubeposleft - cubeposright) / 2,cuberposdown, cuberposfront);
		glVertex3f(cubeposright - (cubeposleft - cubeposright) / 2,cuberposdown, cuberposfront);
		glVertex3f(cubeposright - (cubeposleft - cubeposright) / 2,cuberposdown, cuberposback);
	glEnd();
}
