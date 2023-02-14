#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#define N 4
using namespace std;

// Clipping Window Boundaries
#define XMIN 10
#define YMIN 20
#define XMAX 80
#define YMAX 80

//Point Struct
struct Point{
	float x, y;
};
struct Point Over[40], window[4], outputVer[40];
int Nout;

void drawWindow(Point *p, int n){
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
		glVertex2f(p[i].x,p[i].y);
	glEnd();
	glFlush();
}

void drawPoly(Point *p, int n){
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
		glVertex2f(p[i].x,p[i].y);
	glEnd();
	glFlush();
}

bool insideVertex(Point p, int edge){
	// 0,2 - Horizontal,	1,3 - Vertical (depends)
	switch (edge){
		case 0 : if (p.y >= window[edge].y) return true;		// BOTTOM
				 break;
		case 1 : if (p.x <= window[edge].x) return true;		// RIGHT
				 break;
		case 2 : if (p.y <= window[edge].y) return true;		// TOP
				 break;
		case 3 : if (p.x >= window[edge].x) return true;		// LEFT
				 break;
	}
	return false;
}

void addVertex(Point p){
	Over[Nout++] = p;
}

Point GetIntersect(Point s, Point p, int edge){
	Point res;
	float m = (p.y - s.y) / (p.x - s.x);		//Slope

	if (window[edge].x == window[(edge+1)%4].x){		//Vertical Line
		res.x = window[edge].x;
		res.y = s.y + (res.x - s.x) * m;
	}
	else{										//Horizontal Line
		res.y = window[edge].y;
		res.x = s.x + (res.y - s.y) / m;
	}

	return res;
}

void suther_hodgeman_clip(Point inVer[], int Nin){
	Point s, p;		//src  dest
	Point intersect;

	//Copy input Vertex list
	memcpy(outputVer,inVer,sizeof(outputVer));

	//For each clip window edge
	for (int i = 0; i < 4; i++){
		s = outputVer[Nin - 1];
		Nout = 0;
		//Loop over each polygon edge
		for (int j = 0; j < Nin; j++){
			p = outputVer[j];
			if (insideVertex(p,i)){
				if (insideVertex(s,i)){					// p inside, s inside
					addVertex(p);
				}
				else{									// p inside, s outside
					intersect = GetIntersect(s, p, i);
					addVertex(intersect);
					addVertex(p);
				}
			}
			else{
				if (insideVertex(s,i)){					// p outside, s inside
					intersect = GetIntersect(s, p, i);
					addVertex(intersect);
				}
				else{									// p outside, s outside
					//Do nothing
				}
			}
			s = p;
		}
		memcpy(outputVer,Over,sizeof(Over));
		Nin = Nout;
	}

	glColor3f(1.0,1.0,0.0);
	drawPoly(Over,Nout);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);

	//Create and Draw Clip window
	window[0].x = XMIN;	window[0].y = YMIN;
	window[1].x = XMAX;	window[1].y = YMIN;
	window[2].x = XMAX;	window[2].y = YMAX;
	window[3].x = XMIN;	window[3].y = YMAX;
	drawWindow(window,4);

	//Create and Draw Polygon
	Point inputVer[N];
	inputVer[0].x = 20;	inputVer[0].y = 20;
	inputVer[1].x = 20;	inputVer[1].y = 90;
	inputVer[2].x = 90;	inputVer[2].y = 90;
	inputVer[3].x = 90;	inputVer[3].y = 20;
	glColor3f(1.0,0.0,0.0);
	drawPoly(inputVer,N);

	suther_hodgeman_clip(inputVer,N);

	glFlush();
}

void myInit(){
	glClearColor(1,1,1,1);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,100,0,100);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Sutherland Hodgeman Polygon Clipping");
	myInit();
	glutDisplayFunc(display);
	glutMainLoop();
}