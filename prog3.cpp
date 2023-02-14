#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define dtor 180/3.14157

GLfloat x, y;	//Determine vertices of rec
int sb, db;
static GLfloat theta;

void rectangle(){
	glBegin(GL_QUADS);
		glColor3f(1.0,0.0,0.0);
		glVertex2f(-x,-y);
		glColor3f(0.0,0.0,1.0);
		glVertex2f(y,-x);
		glColor3f(0.0,1.0,0.0);
		glVertex2f(x,y);
		glColor3f(1.0,0.0,1.0);
		glVertex2f(-y,x);
	glEnd();
	glFlush();
}

void spindisplay(){
	theta += 0.0025;
	if (theta > 360.0)
		theta -= 360.0;
	x = cos(theta * (double)dtor);
	y = sin(theta * (double)dtor);
	
	//glRotatef(theta,0.0,0.0,1.0);
	glutSetWindow(db);
	glutPostRedisplay();
}

void disp_single(){
	glClear(GL_COLOR_BUFFER_BIT);
	rectangle();
	glFlush();
}

void disp_double(){
	glClear(GL_COLOR_BUFFER_BIT);
	rectangle();
	glFlush();
	glutSwapBuffers();
}

void myInit(){
	glClearColor(1,1,1,1);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-2.0,2.0,-2.0,2.0);
}

void myreshape(int w, int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,w,h);
	if (w <= h){
		gluOrtho2D(-2.0,2.0,-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h);
	}
	else
		gluOrtho2D(-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h,-2.0,2.0);
	glMatrixMode(GL_MODELVIEW);
}

void mouse (int btn, int state, int x, int y){
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		glutIdleFunc(spindisplay);
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		glutIdleFunc(NULL);
}

int main(int argc, char **argv){
	//Single Buffer
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	sb = glutCreateWindow("Single Buffer");
	myInit();
	glutDisplayFunc(disp_single);
	//glutIdleFunc(spindisplay);
	glutReshapeFunc(myreshape);

	//Double Buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,0);
	db = glutCreateWindow("Double Buffer");
	myInit();
	glutDisplayFunc(disp_double);
	glutIdleFunc(spindisplay);
	glutReshapeFunc(myreshape);
	glutMouseFunc(mouse);
	glutMainLoop();
}