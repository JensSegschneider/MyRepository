/* Rotating cube with color interpolation */


#include <stdlib.h>
#include "stdafx.h"
#include <iostream>
#include "imageloader.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define winsizex 500
#define winsizey 500
#define DEGREES_PER_PIXEL  0.6f

GLuint tex1;
GLuint tex2;
GLfloat x = 0.0f;
GLfloat y = 0.0f;

typedef struct {
	int leftButton;
	int rightButton;
	int x;
	int y;
} MouseState;

MouseState mouseState = { 1, 1, 0, 0 };

void loadPic();
void initRendering();
void polygon(int a, int b, int c, int d, int texture);
void render(void);
GLuint loadTexture(Image* image);
void mouseMove(int x2, int y2);
void mouse(int btn, int state, int x, int y);
void myReshape(int w, int h);
void timer(int value);

	GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
	{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
	{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(winsizex, winsizey);
	glutCreateWindow("OpenGL");
	initRendering();
	glEnable(GL_DEPTH_TEST);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(render);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);
	
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;
}
	
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);


	Image* image1 = loadBMP("Peach.bmp");
	tex1 = loadTexture(image1);

	Image* image2 = loadBMP("Paul.bmp");
	tex2 = loadTexture(image2);

	delete image1;
	delete image2;
}

void polygon(int a, int b, int c, int d, int texture)
{
	/* draw a polygon via list of vertices */
	glEnable(GL_TEXTURE_2D);
	switch (texture){
	case 1:
		glBindTexture(GL_TEXTURE_2D, tex1);
		break;
	case 2:
		glBindTexture(GL_TEXTURE_2D, tex2);
		break;
	}

	glBegin(GL_POLYGON);
	glVertex3fv(vertices[a]);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(vertices[b]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(vertices[c]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(vertices[d]);
	glTexCoord2f(0.0f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void render(void)
{
	/* display callback, clear frame buffer and z buffer,
	rotate cube and draw, swap buffers */

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(x, 1.0f, 0.0f, 0.0f);
	glRotatef(y, 0.0f, 1.0f, 0.0f);
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat directedLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat directedLightPos[] = { -10.0f, 15.0f, 20.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	polygon(0, 3, 2, 1, 1);

	polygon(2, 3, 7, 6, 1);

	polygon(3, 0, 4, 7, 1);

	polygon(1, 2, 6, 5, 2);

	polygon(4, 5, 6, 7, 2);

	polygon(5, 4, 0, 1, 2);
	
	glFlush();
	glutSwapBuffers();
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}

void mouse(int btn, int state, int x, int y)
{
	// update the button state
	if (btn == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
			mouseState.leftButton = 0;
		else
			mouseState.leftButton = 1;
	}
	if (btn == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
			mouseState.rightButton = 0;
		else
			mouseState.rightButton = 1;
	}

	// update the mouse position, so we can track the mouse move
	mouseState.x = x;
	mouseState.y = y;
}

void mouseMove(int x2, int y2)
{
	// Calculate the displacement in movement 
	int xDelta = mouseState.x - x2;
	int yDelta = mouseState.y - y2;

	// Commit the mouse position 
	mouseState.x = x2;
	mouseState.y = y2;

	// If left button is down, change the rotation angle for next frame 
	if (mouseState.leftButton == 0) {
		x -= yDelta * DEGREES_PER_PIXEL;
		y -= xDelta * DEGREES_PER_PIXEL;
	}
	glutPostRedisplay();

}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
		2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat)w / (GLfloat)h,
		2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {
	const int desiredFPS = 120;
	glutTimerFunc(1000 / desiredFPS, timer, ++value);


	glutPostRedisplay();
}