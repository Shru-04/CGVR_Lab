#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define WIN_HEIGHT 500
#define WIN_WIDTH 500

using namespace std;

int xc, yc;		// Center
int pt_done = 0, p0;
int r;
int colorch = 0;

void drawCircle (int xc, int yc, int x, int y){
	//8-fold Sym
	glBegin(GL_POINTS);
	  glVertex2i(xc + x, yc + y);
	  glVertex2i(xc + x, yc - y);
	  glVertex2i(xc - x, yc + y);
	  glVertex2i(xc - x, yc - y);
	  glVertex2i(xc + y, yc + x);
	  glVertex2i(xc + y, yc - x);
	  glVertex2i(xc - y, yc + x);
	  glVertex2i(xc - y, yc - x);
	glEnd();
	glFlush();
}

void Bresenham_Circle(){
	if (colorch == 0){	glColor3f(1.0,0.0,0.0); colorch = 1;	}
	else{	glColor3f(1.0,1.0,0.0); colorch = 0;	}
	
	int x = 0, y = r;
	p0 = 3 - 2*r;
	while (x <= y){
		drawCircle(xc,yc,x,y);
		if (p0 < 0){
			p0 = p0 + 4 * x + 6;
			x++;
		}
		else{
			p0 = p0 + 4 * (x - y) + 10;
			x++;	y--;
		}
		drawCircle(xc,yc,x,y);
	}
	glFlush();
}

void mouse(int btn, int state, int x, int y){
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if (pt_done == 0){
			y = WIN_HEIGHT - y;
			//Center pt
			xc = x;	yc = y;
			pt_done = 1;
		}
		else{
			y = WIN_HEIGHT - y;
			//Radius
			r = (int)sqrt((double)((x - xc) * (x - xc)) + (double)((y - yc) * (y - yc)));
			cout<<"Center : ("<<xc<<","<<yc<<")\tRadius = "<<r<<endl;
			Bresenham_Circle();
			pt_done = 0;
		}
	}
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		glClearColor(1,1,1,1);
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
}

void disp(){}

void myInit(){
	glClearColor(1,1,1,1);
	glPointSize(3);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,WIN_WIDTH,0,WIN_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIN_WIDTH,WIN_HEIGHT);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Bresenham Circle Drawing");
	myInit();
	glutDisplayFunc(disp);
	glutMouseFunc(mouse);
	glutMainLoop();
}