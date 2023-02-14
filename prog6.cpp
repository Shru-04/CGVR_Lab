#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

double theta, thetar, x, y, z, phi, phir, phir20, c80;
const double c = (double)3.14157/(double)180;

void draw_sphere(){
	// for each longitude
	for (phi = -80.0; phi <= 80.0; phi+=10.0){
		//convert to rad
		phir = c * phi;		//1st pt
		phir20 = c * (phi + 20.0);		//2nd pt
		
		if (phi == 0.0)
			glColor3f(1.0,1.0,0.0);

		//for each lattitude
		glBegin(GL_QUAD_STRIP);					//V.IMP
		for (theta = -180.0; theta <= 180.0; theta += 10.0){
			thetar = c * theta;
			//1st pt
			x = sin(thetar) * cos(phir);
			y = cos(thetar) * cos(phir);
			z = sin(phir);
			glVertex3d(x,y,z);

			//2nd pt
			x = sin(thetar) * cos(phir20);
			y = cos(thetar) * cos(phir20);
			z = sin(phir20);
			glVertex3d(x,y,z);
		}
		glEnd();
		glFlush();
	}

	glColor3f(1.0,1.0,0.0);

	//for 1st pole (top) use Triangle Fans
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0,0,1.0);
	c80 = c * 80.0;
	z = sin(c80);
	for (theta = -180.0; theta <= 180.0; theta+=10.0){
		thetar = c * theta;
		x = sin(thetar) * cos(c80);
		y = cos(thetar) * cos(c80);
		glVertex3d(x,y,z);
	}
	glEnd();
	glFlush();

	glColor3f(1.0,0.0,0.0);

	//for 2nd pole (bottom) use Triangle Fans
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0,0,-1.0);
	c80 = c * 80.0;
	z = -sin(c80);
	for (theta = -180.0; theta <= 180.0; theta+=10.0){
		thetar = c * theta;
		x = sin(thetar) * cos(c80);
		y = cos(thetar) * cos(c80);
		glVertex3d(x,y,z);
	}
	glEnd();
	glFlush();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);		//To highlight boundaries/edges
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Make viewing adjustments here...
	glTranslatef(0.0,0.0,-1.0);
	glRotatef(90,0.0,1.0,1.0);
	
	draw_sphere();

	glFlush();
}

void myInit(){
	glClearColor(0,0,0,0);
	//gluOrtho2D(-3.0,3.0,-3.0,3.0);
	glPointSize(2);
	glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Sphere Approx.");
	myInit();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}