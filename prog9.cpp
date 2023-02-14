#include <stdio.h>
#include <GL/glut.h>

double xmin = 50.0, ymin = 50.0, xmax = 150, ymax = 150;		//Clipping Window boundaries
double vxmin = 200, vymin = 200, vxmax = 300, vymax = 300;		//Viewport boundaries

//To test endpoints entering(t1) or leaving(t2)
bool cliptest(double p, double q, double *t1, double *t2){
	double r = q/p;
	if (p < 0.0){			//entering point
		if (r > *t1)	*t1 = r;			//update t1
		if (r > *t2)	return false;		//exterior pt
	}
	else if (p > 0.0){		//leaving point
		if (r < *t2)	*t2 = r;			//update t2
		if (r < *t1)	return false;		//exterior pt
	}
	else{
		if (q < 0.0)	return false;		//parallel to clip window, but outside
	}
	return true;
}

void LiangBarskyClip(double x0, double y0, double x1, double y1){
	double dx = x1 - x0, dy = y1 - y0;
	double t1 = 0.0, t2 = 1.0;

	//Draw Viewport
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
		glVertex2d(vxmin,vymin);
		glVertex2d(vxmax,vymin);
		glVertex2d(vxmax,vymax);
		glVertex2d(vxmin,vymax);
	glEnd();
	glFlush();

	//Updating parameters n inside test (v.imp)
	if (cliptest(-dx,x0 - xmin,&t1,&t2))		//Inside Test wrt LEFT Edge
	if (cliptest(dx,xmax - x0,&t1,&t2))		//Inside Test wrt RIGHT Edge
	if (cliptest(-dy,y0 - ymin,&t1,&t2))		//Inside Test wrt BOTTOM Edge
	if (cliptest(dy,ymax - y0,&t1,&t2))		//Inside Test wrt TOP Edge
	{
		if (t2 < 1.0){			
			//update x1,y1
			x1 = x0 + t2 * dx;		
			y1 = y0 + t2 * dy;
		}
		if (t1 > 0.0){			
			//update x0,y0
			x0 = x0 + t1 * dx;		
			y0 = y0 + t1 * dy;
		}

		//Map window to viewport
		double sx = (vxmax - vxmin) / (xmax - xmin);
		double sy = (vymax - vymin) / (ymax - ymin);
		double vx0 = vxmin + (x0 - xmin) * sx;
		double vy0 = vymin + (y0 - ymin) * sy;
		double vx1 = vxmin + (x1 - xmin) * sx;
		double vy1 = vymin + (y1 - ymin) * sy;
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINES);
			glVertex2d(vx0,vy0);
			glVertex2d(vx1,vy1);
		glEnd();
		glFlush();
	}
	glFlush();
}

void display(){
	double x0 = 20, y0 = 30, x1 = 100, y1 = 100;
	double p0 = 5, q0 = 5, p1 = 170, q1 = 100;
	glClear(GL_COLOR_BUFFER_BIT);
	
	//Draw Clipping Window
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
		glVertex2d(xmin,ymin);
		glVertex2d(xmax,ymin);
		glVertex2d(xmax,ymax);
		glVertex2d(xmin,ymax);
	glEnd();
	glFlush();

	//Draw Lines
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
		glVertex2d(x0,y0);
		glVertex2d(x1,y1);
		glVertex2d(p0,q0);
		glVertex2d(p1,q1);
	glEnd();
	glFlush();

	LiangBarskyClip(x0,y0,x1,y1);
	LiangBarskyClip(p0,q0,p1,q1);

	glFlush();
}

void myInit(){
	glClearColor(1,1,1,1);
	gluOrtho2D(0,500,0,500);
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Liang-Barsky Line Clipping");
	myInit();
	glutDisplayFunc(display);
	glutMainLoop();
}