#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

using namespace std;

float house[9][2] = {{100,100},{210,100},{210,200},{290,200},{290,100},{400,100},{400,250},{250,300},{100,250}};
int angle;		//Rotation angle
float theta, c, m;		//Line
int xp = 100, yp = 100;	//Point of rot

void display_rot(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	//Normal House
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 9; i++)
		glVertex2fv(house[i]);
	glEnd();
	glFlush();

	//Rotated House
	glMatrixMode(GL_MODELVIEW);						//v.v.imp
	glLoadIdentity();
	glPushMatrix();
	
	glTranslatef(xp,yp,0);
	glRotatef(angle,0,0,1);
	glTranslatef(-xp,-yp,0);
	
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 9; i++)
		glVertex2fv(house[i]);
	glEnd();
	glFlush();
	glPopMatrix();
}

void display_ref(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	//Normal House
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 9; i++)
		glVertex2fv(house[i]);
	glEnd();
	glFlush();

	//Line
	float x0 = 500, x1 = 0;
	float y0 = m * x0 + c;
	float y1 = m * x1 + c;
	theta = atan(m);
	theta = theta * 180.0 / 3.14157;	//to deg.
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);
		glVertex2f(x0,y0);
		glVertex2f(x1,y1);
	glEnd();
	glFlush();

	//Reflected House
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	
	glTranslatef(0,c,0);
	glRotatef(theta,0,0,1);
	glScalef(1,-1,1);
	glRotatef(-theta,0,0,1);
	glTranslatef(0,-c,0);

	glColor3f(1.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 9; i++)
		glVertex2fv(house[i]);
	glEnd();
	glFlush();
	glPopMatrix();
}

void simpdisplay(){

}

void mouse(int btn, int state, int x, int y){
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		display_rot();
	}
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		display_ref();
	}
}

void myInit(){
	glClearColor(1,1,1,1);
	glPointSize(2);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-500,500,-500,500);
}

int main(int argc, char **argv){
	cout<<"Enter fixed point coordinates : ";
	cin>>xp>>yp;
	cout<<"Enter Rotation Angle : ";
	cin>>angle;
	cout<<"Enter m and c of line (y = mx + c) : \n";
	cin>>m>>c;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("House Transformation");
	myInit();
	glutDisplayFunc(simpdisplay);
	glutMouseFunc(mouse);
	glutMainLoop();
}