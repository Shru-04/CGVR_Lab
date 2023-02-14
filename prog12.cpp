#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <Windows.h>

using namespace std;

GLfloat vertices[] = {
	-1.0,-1.0,-1.0,
	1.0,-1.0,-1.0,
	1.0,1.0,-1.0,
	-1.0,1.0,-1.0,
	-1.0,-1.0,1.0,
	1.0,-1.0,1.0,
	1.0,1.0,1.0,
	-1.0,1.0,1.0,
};

GLfloat colors[] = {0.0,0.0,0.0,0.0,0.0,1.0,1.0,0.0,1.0,1.0,0.0,0.0,0.0,1.0,1.0,0.0,1.0,0.0,1.0,0.0,0.0,1.0,1.0,1.0};

GLubyte cubeIndices[] = {
	0,3,2,1,
	1,5,6,2,
	2,3,7,6,
	6,5,4,7,
	7,3,0,4,
	4,5,1,0,
};

int axis = 0;  //0 - X, 1 - Y, 2 - Z
GLfloat theta[] = {0.0,0.0,0.0}; 

void cubedisplay(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Rotations
	glMatrixMode(GL_PROJECTION);
	glRotatef(theta[0],1.0,0.0,0.0);
	glRotatef(theta[1],0.0,1.0,0.0);
	glRotatef(theta[2],0.0,0.0,1.0);

	glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,cubeIndices);

	glFlush();
	glutSwapBuffers();
}

void spindisplay(){
	Sleep(250);
	theta[axis] += 2.0;
	if (theta[axis] > 360.0)
		theta[axis] -= 360.0;
	// Regenrate Disp
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		axis = 0;
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		axis = 1;
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		axis = 2;
}


void myInit(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(0,0,0,0);
	glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);

	// Server and Client Side GL caps
	glEnable(GL_DEPTH_TEST);		//Remove hidden-surface
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3,GL_FLOAT,0,colors);
	glVertexPointer(3,GL_FLOAT,0,vertices);
}

int main(int argc, char **argv){
	//Double Buffer
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Cube Spin");
	myInit();
	glutIdleFunc(spindisplay);	//Spinning in bg
	glutMouseFunc(mouse);
	glutDisplayFunc(cubedisplay);
	glutMainLoop();
	return 0;
}