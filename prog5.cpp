#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#define W_WIDTH 500
#define W_HEIGHT 500

typedef GLfloat point[3];		//V.imp
using namespace std;

point tetra[4] = {{0,250,-250},{-250,-250,-250},{250,-250,-250},{0,0,250}};
int iter;	//No. of Subdivison

void draw_triangle(point p1, point p2, point p3){
	//Draw each triangle face
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);
}

void draw_tetrahedron(point p1, point p2, point p3, point p4){
	//Draw 4 faces of tetrahedron
	glColor3f(0.0,0.0,0.0);
	draw_triangle(p1,p2,p3);
	glColor3f(0.0,1.0,0.0);
	draw_triangle(p2,p3,p4);
	glColor3f(0.0,0.0,1.0);
	draw_triangle(p1,p3,p4);
	glColor3f(1.0,0.0,0.0);
	draw_triangle(p1,p2,p4);
}

void divide_tetrahedron(point p1, point p2, point p3, point p4, int m){
	point mid[6];		//Store mid-points of 6 edges

	for (int j = 0; j < 3; j++)	mid[0][j] = (p1[j] + p2[j]) / 2;
	for (int j = 0; j < 3; j++)	mid[1][j] = (p1[j] + p3[j]) / 2;
	for (int j = 0; j < 3; j++)	mid[2][j] = (p1[j] + p4[j]) / 2;
	for (int j = 0; j < 3; j++)	mid[3][j] = (p2[j] + p3[j]) / 2;
	for (int j = 0; j < 3; j++)	mid[4][j] = (p2[j] + p4[j]) / 2;
	for (int j = 0; j < 3; j++)	mid[5][j] = (p3[j] + p4[j]) / 2;

	if (m > 0){
		divide_tetrahedron(p1,mid[0],mid[1],mid[2],m-1);				
		divide_tetrahedron(p2,mid[0],mid[3],mid[4],m-1);
		divide_tetrahedron(p3,mid[1],mid[3],mid[5],m-1);
		divide_tetrahedron(p4,mid[2],mid[4],mid[5],m-1);
	}
	else{
		draw_tetrahedron(p1,p2,p3,p4);
		glFlush();
	}
}

void disp_tetra(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//V.IMP
	glBegin(GL_TRIANGLES);
	divide_tetrahedron(tetra[0],tetra[1],tetra[2],tetra[3],iter);		//To draw tetrahedron 
	glEnd();
	glFlush();
}

void myInit(){
	glClearColor(1,1,1,1);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-300,300,-300,300,-300,300);		//V.Imp
}

int main(int argc, char **argv){
	cout<<"Enter the no. of subdivisions : ";
	cin>>iter;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(W_WIDTH,W_HEIGHT);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Sierpinski Gasket");
	myInit();
	glutDisplayFunc(disp_tetra);
	glutMainLoop();
	return 0;
}