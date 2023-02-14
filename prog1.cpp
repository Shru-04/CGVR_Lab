#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

int click = 0, X0, Y0, X1, Y1;

void drawpixel(int x, int y){
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	  glVertex2i(x,y);
	glEnd();
	glFlush();
}

void Bresenham_Line(int xc0, int yc0, int xc1, int yc1){
	int dx = xc1 -xc0, dy = yc1 - yc0, d0;
	int incx = 1, incy = 1;
	
	if (dx < 0){	//-ve slope
		dx = -dx;
		incx = -1;
	}

	if (dy < 0){	//-ve slope
		dy = -dy;
		incy = -1;
	}

	//Vertical Line
	if (dx == 0){
		drawpixel(xc0,yc0);
		for (int i = 0; i < dy; i++){
			yc0 = yc0 + incy;
			drawpixel(xc0,yc0);
		}
		glFlush();
		return;
	}

	//Horizontal Line
	if (dy == 0){
		drawpixel(xc0,yc0);
		for (int i = 0; i < dx; i++){
			xc0 = xc0 + incx;
			drawpixel(xc0,yc0);
		}
		glFlush();
		return;
	}

	//Normal Line
	if (dy <= dx){						//m <= 1
		drawpixel(xc0,yc0);
		d0 = 2*dy - dx;
		for (int i = 0; i < dx; i++){
			if (d0 < 0){
				d0 = d0 + 2 * dy;
				xc0 = xc0 + incx;
			}
			else{
				d0 = d0 + 2 * (dy - dx);
				xc0 = xc0 + incx;
				yc0 = yc0 + incy;
			}
			drawpixel(xc0,yc0);
		}
	}
	else{
		drawpixel(xc0,yc0);
		d0 = 2*dx - dy;
		for (int i = 0; i < dy; i++){
			if (d0 < 0){
				d0 = d0 + 2 * dx;
				yc0 = yc0 + incy;
			}
			else{
				d0 = d0 + 2 * (dx - dy);
				yc0 = yc0 + incy;
				xc0 = xc0 + incx;
			}
			drawpixel(xc0,yc0);
		}
	}

	glFlush();
}

void mouse (int btn, int state, int x, int y){
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && click == 0){
		Y0 = 500 - y;
		X0 = x;
		cout<<"Point 1 is ("<<X0<<","<<Y0<<")"<<endl;
		click = 1;
	}
	else if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && click){
		Y1 = 500 - y;
		X1 = x;
		cout<<"Point 2 is ("<<X1<<","<<Y1<<")"<<endl;
		Bresenham_Line(X0,Y0,X1,Y1);
		click = 0;
	}
}

void myInit(){
	glClearColor(1,1,1,1);
	glMatrixMode(GL_PROJECTION);
	glLineWidth(2.0);
	gluOrtho2D(0,500,0,500);
	glClear(GL_COLOR_BUFFER_BIT);
}

void mydisp(){}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Bresenham Line Drawing");
	myInit();
	glutDisplayFunc(mydisp);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}