#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
using namespace std;

double xmin = 50, ymin = 50, xmax = 150, ymax = 150;	//Clipping Window
double xvmin = 200, yvmin = 200, xvmax = 400, yvmax = 400;	//Viewport
const int TOP = 8;
const int BOTTOM = 4;
const int LEFT = 1;
const int RIGHT = 2;

int compute_outcode(double x, double y){
	int code = 0;
	if (y > ymax)	code |= TOP;
	else if (y < ymin)	code |= BOTTOM;
	if (x > xmax)	code |= RIGHT;
	else if (x < xmin)	code |= LEFT;
	
	return code;
}

void cohen_sutherland(double x0, double y0, double x1, double y1){
	int outcode0, outcode1, outcodeout;
	double x, y;
	double m = (y1 - y0) / (x1 - x0);
	
	//Logic
	bool accept = false, done = false;
	outcode0 = compute_outcode(x0,y0);
	outcode1 = compute_outcode(x1,y1);
	do{
		outcodeout = outcode0 ? outcode0 : outcode1;				///v.imp
		if (!(outcode0 | outcode1)){			//Inside clip window, accept
			accept = true;
			done = true;
		}
		else if (outcode0 & outcode1){			//Outside clip window, reject
			done = true;
		}
		else{
			if (outcodeout & TOP){			//v.imp		(find intersections)
				x = x0 + (ymax - y0)/m;
				y = ymax;
			}
			else if (outcodeout & BOTTOM){			
				x = x0 + (ymin - y0)/m;
				y = ymin;
			}
			else if (outcodeout & RIGHT){			
				x = xmax;
				y = y0 + m*(xmax - x0);
			}
			else if (outcodeout & LEFT){			
				x = xmin;
				y = y0 + m*(xmin - x0);
			}

			//Update coordinates
			if (outcodeout == outcode0){
				x0 = x;
				y0 = y;
				outcode0 = compute_outcode(x0,y0);
			}
			else{
				x1 = x;
				y1 = y;
				outcode1 = compute_outcode(x1,y1);
			}
		}
	}while (!done);

	if (accept){
		//Map to viewport
		double sx = (xvmax - xvmin) / (xmax - xmin);
		double sy = (yvmax - yvmin) / (ymax - ymin);
		
		double xv0 = xvmin + (x0 - xmin) * sx;
		double yv0 = yvmin + (y0 - ymin) * sy;
		double xv1 = xvmin + (x1 - xmin) * sx;
		double yv1 = yvmin + (y1 - ymin) * sy;

		//Draw Viewport and lines
		glColor3f(0,0,0);
		glBegin(GL_LINE_LOOP);
			glVertex2d(xvmin, yvmin);
			glVertex2d(xvmax, yvmin);
			glVertex2d(xvmax, yvmax);
			glVertex2d(xvmin, yvmax);
		glEnd();
		glFlush();

		glColor3f(1,0,1);
		glBegin(GL_LINES);
			glVertex2d(xv0, yv0);
			glVertex2d(xv1, yv1);
		glEnd();
		glFlush();
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	double x0 = 30, y0 = 10, x1 = 180, y1 = 100;
	//Draw Clipping Window
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
		glVertex2d(xmin, ymin);
		glVertex2d(xmax, ymin);
		glVertex2d(xmax, ymax);
		glVertex2d(xmin, ymax);
	glEnd();
	glFlush();

	//Draw Lines
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
		glVertex2d(x0,y0);
		glVertex2d(x1,y1);
	glEnd();
	glFlush();

	cohen_sutherland(x0,y0,x1,y1);

	glFlush();
}

void myInit(){
	glClearColor(1,1,1,1);
	glPointSize(2);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,500,0,500);
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Cohen-Sutherland Clipping");
	myInit();
	glutDisplayFunc(display);
	glutMainLoop();
}