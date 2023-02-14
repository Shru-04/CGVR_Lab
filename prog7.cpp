#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <GL/glut.h>
#include <Windows.h>
#define win_width 500
#define win_height 500

using namespace std;
double x[500], y[500];	//Vertices
int m, n;
static double intx[20];

void drawLine(double x0, double y0, double x1, double y1){
	Sleep(10);
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_LINES);
		glVertex2d(x0,y0);
		glVertex2d(x1,y1);
	glEnd();
	glFlush();
}

void edgeIntersect(double x1, double y1, double x2, double y2, int scl){
	double tmp;
	if (y2 < y1){
		tmp = y1;	y1 = y2;	y2 = tmp;
		tmp = x1;	x1 = x2;	x2 = tmp;
	}
	if (scl > y1 && scl < y2)		//Edge intersect
		intx[m++] = x1 + (scl - y1) * (x2 - x1)/(y2 - y1);
}

void scanline_fill(double x[], double y[]){
	for (int sl = 0; sl <= win_height; sl++){
		m = 0;
		//Find edge x-intercepts
		for (int i = 0; i < n; i++)
			edgeIntersect(x[i],y[i],x[(i+1)%n],y[(i+1)%n],sl);

		//Sort em
		sort(intx,intx + m);
		
		//Fill interior
		if (m >= 2){
			for (int i = 0; i < m; i+=2)
				drawLine(intx[i],sl,intx[i+1],sl);
		}
	}
	glFlush();
}

void disp_poly(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	//Draw Polygon
	glBegin(GL_LINE_LOOP);			//vv.imp
	for (int i = 0; i < n; i++)
		glVertex2d(x[i],y[i]);
	glEnd();
	glFlush();

	scanline_fill(x,y);
	glFlush();
}

void myInit(){
	glClearColor(1,1,1,1);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,win_width,0,win_height);
}

int main(int argc, char **argv){
	cout<<"Enter the no. of vertices of polygon : ";
	cin>>n;
	cout<<"Enter the vertices :\n";
	for (int i = 0; i < n; i++)
		cin>>x[i]>>y[i];
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(win_width,win_height);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Scanline Fill Algo");
	myInit();
	glutDisplayFunc(disp_poly);
	glutMainLoop();
	return 0;
}