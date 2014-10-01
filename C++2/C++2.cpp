#include "stdafx.h"
#include <GL/glut.h>

#pragma region defines

#define changeline 4
#define changepat 3
#define changepx 1
#define changevis 2
#define cuberposdown -0.25
#define cubeposleft -0.25
#define cubeposright 0.25
#define cuberposup 0.25
#define winposx 100
#define winposy 100
#define winsizex 500
#define winsizey 500

#pragma endregion

#pragma region methodHeaders

void addElement(GLfloat vertrices[], GLubyte color[], GLenum type);
void paint(void);
void processMenuEvents(int);
void render(void);

#pragma endregion

#pragma region globalValues

bool showdiagonals = true;
bool showfilled = true;
bool showline = true;
float width = 1;

#pragma endregion

#pragma region init

int main(int argc, char **argv)
{
	int menu;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(winposx,winposy);
	glutInitWindowSize(winsizex,winsizey);
	glutCreateWindow("OpenGL");
	glutDisplayFunc(render);
	menu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("ChangePixel",changepx);
	glutAddMenuEntry("ChangeVis",changevis);
	glutAddMenuEntry("FillPattern",changepat);
	glutAddMenuEntry("ChangeLine",changeline);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}

#pragma endregion

#pragma region methods

void addElement(GLfloat vertrices[], GLubyte color[], GLenum type){
	glVertexPointer(2,GL_FLOAT,0,vertrices);
	glColorPointer(3,GL_UNSIGNED_BYTE,0,color);
	switch (type)
	{
		case GL_LINES:
			glDrawArrays(type,0,2);
		break;
		case GL_QUADS: 
		case GL_LINE_LOOP:
			glDrawArrays(type,0,4);
		break;
	}
}

void paint(void){
	glEnable(GL_VERTEX_ARRAY); 
	glEnable(GL_COLOR_ARRAY);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineStipple(1, 0x3F07);
	glLineWidth(width);
	if(showline)
	{
		glEnable(GL_LINE_STIPPLE);
	} 
	else
	{
		glDisable(GL_LINE_STIPPLE);
	}
	GLfloat squareShapeVertices[] ={cubeposleft,cuberposdown, cubeposright,cuberposdown, cubeposright,cuberposup, cubeposleft,cuberposup};
	GLubyte squareVertexColours[] ={255,0,0, 0,255,0, 0,0,255, 0,255,255};
	if (showfilled)
	{
		addElement(squareShapeVertices, squareVertexColours, GL_QUADS);
	}
	else
	{
		addElement(squareShapeVertices, squareVertexColours, GL_LINE_LOOP);
	}
	if(showdiagonals)
	{
		GLubyte lineVertexColours[] ={0,0,0, 0,0,0, 0,0,0, 0,0,0};
		GLfloat lineShapeVertices[] = {cubeposleft,cuberposdown, cubeposright,cuberposup};
		addElement(lineShapeVertices, lineVertexColours, GL_LINES);
		GLfloat lineShapeVertices2[] = {cubeposright,cuberposdown, cubeposleft,cuberposup};
		addElement(lineShapeVertices2, lineVertexColours, GL_LINES);
	}
	glutSwapBuffers();
	glDisable(GL_VERTEX_ARRAY); 
	glDisable(GL_COLOR_ARRAY);
}

void processMenuEvents(int option) {
	switch(option)
	{
	case 1:
		width = width == 1 ? 2 : 1;
		break;
	case 2:
		showdiagonals = !showdiagonals;
		break;
	case 3:
		showfilled = !showfilled;
		break;
	case 4:
		showline = !showline;
		break;
	}
	paint();
}

void render(void){
	paint();
}

#pragma endregion
