#include <iostream>
#include <math.h>
#include <GL/glut.h>

using namespace std;

int d1, d2;

void draw_pixel(int xc, int yc, int x, int y){
	glColor3f(1,0,0);
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

void BresCircle(int xc, int yc, int r){
	int p0 = 3 - 2*r;
	int x = 0, y = r;
	while (x <= y){
		draw_pixel(xc,yc,x,y);
		if (p0 < 0){
			p0 = p0 + 4*x + 6;
			x++;
		}
		else{
			p0 = p0 + 4*(x - y) + 10;
			x++;	y--;
		}
		draw_pixel(xc,yc,x,y);
	}
	glFlush();
}

void cylinder(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	int x = 250, y = 250, r = 150, n = 100;
	for (int i = 0; i <= n; i++){
		BresCircle(x,y+i,r);
	}
	glFlush();
	glutSetWindow(d1);
}

void draw_rect(int x0, int y0, int x1, int y1){
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);		//V.V.V.IMP
		glVertex2i(x0,y0);
		glVertex2i(x0,y1);
		glVertex2i(x1,y1);
		glVertex2i(x1,y0);
	glEnd();
	glFlush();
}

void parallelopiped(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,1.0);
	int x0 = 100, x1 = 200, y0 = 100, y1 = 200, n = 50;
	for (int i = 0; i <= n; i++)
		draw_rect(x0 + i, y0 + i, x1 + i, y1 + i);
	glFlush();
	glutSetWindow(d2);
}

void myInit(){
	glClearColor(1,1,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	d1 = glutCreateWindow("Cylinder");
	glutSetWindow(d1);
	myInit();
	glutDisplayFunc(cylinder);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,0);
	d2 = glutCreateWindow("Parallelopiped");
	glutSetWindow(d2);
	myInit();
	glutDisplayFunc(parallelopiped);
	glutMainLoop();
	return 0;
}