// C++5.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <GL\glut.h>
#define winposx 100
#define winposy 100
#define winsizex 500
#define winsizey 500
#define Lnumber 256

void render();
void drawcheck(float x, float y, float z);

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(winposx,winposy);
	glutInitWindowSize(winsizex,winsizey);
	glutCreateWindow("OpenGL");
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}

void render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_COLOR_LOGIC_OP);
	glLogicOp(GL_XOR);
	glLoadIdentity();
	drawcheck(0,0,0);
	drawcheck(-1,-1,0);
	glDisable(GL_COLOR_LOGIC_OP);
	glutSwapBuffers();
}

void drawcheck(float x, float y, float z){
	GLubyte wb[2]={0x00, 0xFF};
	GLubyte check[Lnumber * 8];
	int i,j;
	for (i=0;i<Lnumber;i++)
		for (j=0; j<8; j++)
			check[i*8+j] = wb[(i/8+j)%2];
	glColor3f(255,0,0);
	glRasterPos3f(x, y, z);
	glBitmap(Lnumber / 2,Lnumber / 2,0.0,0.0,0.0,0.0,check);
	glColor3f(0,255,0);
	glRasterPos3f(x, y, z);
	glBitmap(Lnumber / 2,Lnumber / 2,4,-4,0.0,0.0,check);
}