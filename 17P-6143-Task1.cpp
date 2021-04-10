/*
Name: Abdul Aziz Muhammad Ibrahim Isa
Roll No: P17-6143
Title: Computer Graphics Assignment # 3
Submitted to: Dr Omar Usman Khan
Description:
In this assignment we were required to use Mass(of the ball), Force(applied on the ball),
acceleration(of the ball), initial and final velocity(of the ball), time and distance.
To compute all this I had to assume some values:
		mass = 200g ( we will do the computations in kg as N = kgm/s^2),
		Force = 5N,
		initial velocity = 5 m/s.
All other values have been calculated using these 3 values.
When the ball is in the air the force acting on it is w (w = mg), therefore when the  ball 
will be in air we will take acceleration as g (9.8 m/s^2)
As OpenGL does not support multiple keypresses I have used an array to store the keypresses, This method is not very 
responsive but atleast it works.

*/

#include"GL/glut.h"
#include <cmath>
#include <random>
#include<iostream>
using namespace std;
#define PI 3.142
unsigned int ID;
int state = -1;
float ybase = -37;
float horizontalR = 48.5;//right window boundary for the ball
float horizontalL = -48.5;//left window boundary for the ball
float xMax, XMin, YMax, YMin;
GLfloat x1 = -47;// base coordinates
GLfloat yy = -37;// base coordinates
GLfloat vi = 5.0;//initail velocity
GLfloat radius = 3.0;// radius of the ball
GLfloat  vx, vy, sx, sy, s, a, t, increment, decrement;
GLfloat g = 9.8;// acceleration in freefall
GLfloat force = 5;// 5N force applied on the ball
GLfloat mass = 0.2; // mass of ball 200 grams which is 0.2KG
GLfloat frames = 60.0;// how many frames in one second FPS
bool keystatus[256] = { false };// to store values for keys if they are pressed or not( used for multiple key presses).

void drawFilledCircleLeft() {
	YMax = x1 + radius;
	YMin = x1 - radius;
	int i;
	int triangleAmount = 50; 
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.9, 0.3, 0.2);
	glVertex2f(x1, yy); 
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(x1 + (radius * cos(i *  twicePi / triangleAmount)), yy + (radius * sin(i * twicePi / triangleAmount)));
	}
	glEnd();
	glutSwapBuffers();
	
}
void LoadTextures(const char*filename)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void display() {
	glClear(GL_CLEAR);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ID);
	/*glBindTexture(GL_TEXTURE_2D, // GL_TEXTURE_2D, GL_PROXY_TEXTURE_CUBE_MAP (Others Too)
		ID);
	glTexImage2D(GL_TEXTURE_2D, // GL_TEXTURE_2D, GL_PROXY_TEXTURE_CUBE_MAP (Others Too)
		0, // Detail that is required (0 is basic)
		GL_RED, // Texture (GL_RED, GL_RG, GL_RGB, GL_RGBA)
		1, 1, // Acquired from stbi_load (Mus t be powers two)
		0, // Border = 0
		GL_RED, // Image (GL_RED, GL_RG, GL_RGB, GL_RGBA)
		GL_UNSIGNED_BYTE, // GL_UNSIGNED_BYTE (or others)
		&ID)*/;
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex2f(-50, -50);
	glTexCoord2f(1.0, 0.0); glVertex2f(50, -50);
	glTexCoord2f(1.0, 1.0); glVertex2f(50, -40);
	glTexCoord2f(0.0, 1.0); glVertex2f(-50, -40);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glClearColor(0.0, 1, 1, 1);
	drawFilledCircleLeft();
}
void reshape(GLsizei width, GLsizei height) {
	gluOrtho2D(-50, 50, -50, 50);
}
void timer(int)
{
	if (state == 1)
	{
		if (x1 <= horizontalR)
		{
			x1 = x1 + increment;
		}
		else
		{
			x1 = x1 - 2*increment;
			state = -1;
		}
	}
	if (state == 2)
	{
		if (x1 >= horizontalL)
		{
			x1 = x1 - decrement;
		}
		else
		{
			x1 = x1 + 2*decrement;
			state = -1;
		}
	}
	if (state == 3)
	{
		if (yy <= sy)
		{
			yy = yy + increment;
		}
		else
		{
			decrement = increment;
			state = 4;
		}
	}
	if (state == 4)
	{
		if (yy >= ybase)
		{
			yy = yy - decrement;
		}
		else
		{
			if (sy > 10)
			{
				sy = sy / 2;
				increment = increment - (0.25* increment);
				state = 3;
			}
			else if (sy > 0)
			{
				s = sy;
				sy = sy - (2 * s);
				increment = increment - (0.25* increment);
				state = 3;
			}
			else if (sy < 0)
			{
				s = sy;
				sy = sy + (s);
				increment = increment - (0.25* increment);
				state = 3;
			}
		
		}
		if (sy <= ybase && yy <= ybase)
		{
			state = -1;
		}
	}
	if (state == 5)
	{
		if (yy <= sy)
		{
			yy = yy + increment;
			x1 = x1 + increment;
		}
		if (x1 >= horizontalR )
		{
			decrement = increment;
			state = 4;
		}
		if(yy>= sy)
		{
			decrement = increment;
			state = 6;
		}
	}
	if (state == 6)
	{
		if (yy >= ybase)
		{
			yy = yy - decrement;
			x1 = x1 + increment;
		}
		if (x1 >= horizontalR)
		{
			decrement = increment;
			state = 4;
		}
		if (yy <= ybase)
		{
			state = -1;
		}
	}
	if (state == 7)
	{
		if (yy <= sy)
		{
			yy = yy + increment;
			x1 = x1 - decrement;
		}
		if (x1 + 0.5 <= horizontalL)
		{
			decrement = increment;
			state = 4;
		}
		if (yy >= sy)
		{
			decrement = increment;
			state = 8;
		}
	}
	if (state == 8)
	{
		if (yy >= ybase)
		{
			yy = yy - decrement;
			x1 = x1 - decrement;
		}
		if (x1 + 0.5 <= horizontalL)
		{
			state = 4;
		}
		if (yy <= ybase)
		{
			state = -1;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(1000 / frames, timer, 0);
}
void keyboard(int key, int x, int y)
{
	keystatus[key] = true;
	if (keystatus[GLUT_KEY_RIGHT] == true && keystatus[GLUT_KEY_UP] == true)
	{
		if (horizontalR - x1 <= 3)
		{
			//cout << "do nothing" << endl;
		}
		else
		{
			sy = yy + pow(vi, 2) / 2 * g;
			sy = sy / 8;
			t = vi / g;
			increment = (sy / t) / frames;
			state = 5;
			glutTimerFunc(0, timer, 0);
		}
		
		keystatus[GLUT_KEY_RIGHT] = false;
		keystatus[GLUT_KEY_UP] = false;
	}
	if (keystatus[GLUT_KEY_LEFT] == true && keystatus[GLUT_KEY_UP] == true)
	{
		if (horizontalL - x1 <= 3 && horizontalL - x1 >= 0)
		{
			//cout << "do nothing" << endl;
		}
		else
		{
			sy = yy + pow(vi, 2) / 2 * g;
			sy = sy / 8;
			t = vi / g;
			increment = (sy / t) / frames;
			decrement = increment;
			state = 7;
			glutTimerFunc(0, timer, 0);
		}
		keystatus[GLUT_KEY_LEFT] = false;
		keystatus[GLUT_KEY_UP] = false;

	}
	switch (key)
	{
	case GLUT_KEY_RIGHT: {
		if (yy > ybase)
		{
			//cout << "do nothing " << endl;
			break;
		}
		else
		{
			a = (force / mass);
			sx = 50 - x1;
			vx = pow(((2 * a * sx) + pow(vi, 2)), 0.5);
			t = (vx - vi) / a;
			increment = (sx / t) / frames;
			state = 1;
			glutTimerFunc(0, timer, 0);
			break;
		}
		
	}
	case GLUT_KEY_LEFT: {
		if (yy > ybase)
		{
			//cout << "do nothing " << endl;
			break;
		}
		else
		{
			a = (force / mass);
			sx = 50 + x1;
			vx = pow(((2 * a * sx) + pow(vi, 2)), 0.5);
			t = (vx - vi) / a;
			decrement = (sx / t) / frames;
			state = 2;
			glutTimerFunc(0, timer, 0);
			break;
			
		}
		
	}
	case GLUT_KEY_UP: {
		sy =  yy + pow(vi, 2) / 2 * g;
		t = vi / g;
		increment = (sy / t) / frames;
		state = 3;
		glutTimerFunc(0, timer, 0);
		break;
	}
	
	}
	glutPostRedisplay();
}
void keyboardup(int key, int x, int)
{
	keystatus[key] = false;
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);   // Set the window's initial width & height
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Basic Game Physics");
	glutInitDisplayMode(GL_DOUBLE);
	LoadTextures("brick.png");
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);
	glutSpecialUpFunc(keyboardup);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
}