#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include <GL/glut.h>

double min = INFINITY, max = -INFINITY;
int X[100], Y[100];
int c = 0;
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 500.0, 500.0, 0.0, 1.0, -1.0); //As an example
	glMatrixMode(GL_MODELVIEW);
}

double alpha = 0.01;
double a = 0,b = 0;
void linear()
{
	double xsum = 0, x2sum = 0, ysum = 0, xysum = 0;                //variables for sums/sigma of xi,yi,xi^2,xiyi etc
	for (int i = 0; i < c; i++)
	{
		xsum = xsum + X[i];                        //calculate sigma(xi)
		ysum = ysum + Y[i];                        //calculate sigma(yi)
		x2sum = x2sum + pow(X[i], 2);                //calculate sigma(x^2i)
		xysum = xysum + X[i] * Y[i];                    //calculate sigma(xi*yi)
	}
	a = (c * xysum - xsum * ysum) / (c * x2sum - xsum * xsum);            //calculate slope
	b = (x2sum * ysum - xsum * xysum) / (x2sum * c - xsum * xsum);            //calculate intercept
	//double y_fit[100];                        //an array to store the new fitted values of y    
	/*for (int i = 0; i < c; i++)
		y_fit[i] = a * X[i] + b;*/
	
	//printf("dd\n");
//	cout << w << "\t" << b << endl;
}

void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			if (x < min) min = x;
			if (x > max) max = x;
			X[c] = x;
			Y[c] = y;
			//printf("%d,%d\n", X[c], Y[c]);
			c++;
			if (c > 1)
			{
				linear();
			}
		}
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5);
	//draw two points

	for (int i = 0; i < c; i++)
	{

		glBegin(GL_POINTS);

		glVertex2i(X[i], Y[i]);
		glEnd();
	}
	glBegin(GL_LINES);
	glVertex2f(min, a * min + b);
	glVertex2f(max, a * max + b);
	glEnd();
	glFlush();
	glutSwapBuffers();
	////glBegin(GL_POINTS);

	//glVertex2f(10, 10);
	////glEnd();


	glFlush();

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("points and lines");
	glutMouseFunc(mouseFunc);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 1;
}