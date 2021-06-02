// Skeleton code
#include <windows.h>
#include <time.h>
#include <math.h>
#define GLUT_DISABLE_ATEXIT_HACK // In case of errors like undefined reference to `__glutInitWithExit@12’, should be before including glut.h 
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glut.h>

int screenWidth = 600;
int screenHeight = 600;
float  sphi = 0.0, stheta = 0.0;
float  sside = 0, sdepth = -5;
float  sx = 0, sy = 0;
bool  mouse_left_click;
int   mouseX, mouseY;
GLfloat angle = 0.0f;
int refreshmill = 15;
static int rotateAngle = 0;
static int window;
static int menu_id;
static int submenu_id;
static int value = 0;

void init() //Performs application specific initialization
{
	glColor3f(0.0f, 0.0f, 0.0f);  // set color of stuff
	glShadeModel(GL_FLAT);	// or can be GL_SMOOTH

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Replaces the current matrix with the identity matrix.

	// Produce the perspective projection
	gluPerspective(45.0f, 1.0, 1.0, 100.0);
	gluLookAt(-4, 7, -4, -1, 1, 5, 0.1, 0.5, 0); //Creates a viewing matrix derived from an eye point, 
												 //a reference point indicating the center of the scene, and an UP vector
	glMatrixMode(GL_MODELVIEW);

}

void wireBox(GLdouble width, GLdouble height, GLdouble depth) { //Draws a wireframe box
	glPushMatrix(); //Pushes the current matrix stack down by one, duplicating the current matrix.
	glScalef(width, height, depth);
	glutWireCube(1.0);
	glPopMatrix(); //Pops the current matrix stack, replacing the current matrix with the one below it on the stack.
}

void constantLine(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat xend, GLfloat yend, GLfloat zend)
{
	////Draws steering wheel lines, tires lines, axles, steering column and shaft.
	glBegin(GL_LINES);
	glVertex3f(x0, y0, z0);
	glVertex3f(xend, yend, zend);
	glEnd();

}

void drawCircle(float cx, float cy, float cz, float r, int num_segments) //Draws tires and steering wheel.
{
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		float z = cz;
		glVertex3f(x + cx, y + cy, z);//output vertex 
	}
	glEnd();
	glPopMatrix();

}

void revolve(int key, int, int) { //Handles the keyboard event: the left and right arrow keys change direction of the tires.
	switch (key) {
	case GLUT_KEY_LEFT: (rotateAngle += 5) %= 360; break;
	case GLUT_KEY_RIGHT: (rotateAngle -= 5) %= 360; break;
	default: return;
	}
	glutPostRedisplay(); //Marks the current window as needing to be redisplayed.
}

void movingCircle1() //Draws one of front tires and rotates it left or right direction when the user press arrow keys.
{	
	glPushMatrix();
	glTranslatef(1.8,-0.4,1.3);
	glRotatef((GLfloat)rotateAngle, 0.0, 1.0, 0.0); //Provides revolve of tires left and right direction
	glTranslatef(-1.8,0.4,-1.3);
	drawCircle(1.8, -0.4, 1.3, 0.5, 360); 
	glPopMatrix();
}

void movingCircle2() //Draws one of front tires and rotates it left or right direction when the user press arrow keys.
{
	glPushMatrix();
	glTranslatef(1.8, -0.4, -1.3);
	glRotatef((GLfloat)rotateAngle, 0.0, 1.0, 0.0);
	glTranslatef(-1.8, 0.4, 1.3);
	drawCircle(1.8, -0.4, -1.3, 0.5, 360);
	glPopMatrix();
}

void steeringWheel() { //Draws and rotates steering wheel.
	glPushMatrix();
	
	glRotated(90, 1, 0, 0);
	drawCircle(1.6, 0.1, -2, 0.4, 360);
	glPopMatrix();
}


void frontTireLines1() { //Draws line one of the front tires and rotates line constantly. 
						//It rotates line left or right direction when user press arrow keys.
	glPushMatrix();
	glTranslatef(1.8, -0.4, 1.3);
	glRotatef((GLfloat)rotateAngle, 0.0, 1.0, 0.0);
	glTranslatef(-1.8, 0.4, -1.3);
	glTranslatef(1.8, -0.4, 1.3);
	glRotatef(angle, 0.0f, 0.0f, 1.0f); //Makes the line rotate around its center.
	glTranslatef(-1.8, 0.4, -1.3);
	constantLine(2.3, -0.4, 1.3, 1.3, -0.4, 1.3);
	glPopMatrix();
}

void frontTireLines2() { //Draws line one of the front tires and rotates line constantly. 
						//It rotates line left or right direction when user press arrow keys.
	glPushMatrix();
	glTranslatef(1.8, -0.4, -1.3);
	glRotatef((GLfloat)rotateAngle, 0.0, 1.0, 0.0);
	glTranslatef(-1.8, 0.4, 1.3);
	glTranslatef(1.8, -0.4, -1.3);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-1.8, 0.4, 1.3);
	constantLine(2.3, -0.4, -1.3, 1.3, -0.4, -1.3);
	glPopMatrix();
}

void backTireLines1() { //Draws line one of the back tires and rotates line constantly.
	glPushMatrix();
	glTranslatef(-1.8, -0.4, 1.3);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(1.8, 0.4, -1.3);
	constantLine(-2.3, -0.4, 1.3, -1.3, -0.4, 1.3);
	glPopMatrix();
}

void backTireLines2() {	//Draws line one of the back tires and rotates line constantly.
	glPushMatrix();
	glTranslatef(-1.8, -0.4, -1.3);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(1.8, 0.4, 1.3);
	constantLine(-2.3, -0.4, -1.3, -1.3, -0.4, -1.3);
	glPopMatrix();
}

void steeringWheelLine1() { //Draws line one of the steering wheel lines and rotates line left or right direction when user press arrow keys.
	glPushMatrix();
	glTranslatef(1.6, 2, 0.1);
	glRotatef((GLfloat)rotateAngle, 0.0, 0.1, 0.0);
	glTranslatef(-1.6, -2, -0.1);
	constantLine(1.2, 2, 0.1, 2, 2, 0.1);
	glPopMatrix();
}

void steeringWheelLine2() { //Draws line one of the steering wheel lines and rotates line left or right direction when user press arrow keys.
	glPushMatrix();
	glTranslatef(1.6, 2, 0.1);
	glRotatef((GLfloat)rotateAngle, 0.0, 0.1, 0.0);
	glTranslatef(-1.6, -2, -0.1);
	constantLine(1.6, 2, -0.3, 1.6, 2 ,0.5);
	glPopMatrix();
}

void timer(int value) { //This method helps animation of car, includes glutTimerFunc.
	glutPostRedisplay();
	glutTimerFunc(refreshmill, timer, 0); //Registers a timer callback to be triggered in a specified number of milliseconds.
}

void reshape(int width, int height)
{ // adjust the camera aspect ratio to match that of the viewport
	glViewport(0, 0, width, height); // update viewport
	//glOrtho(-width,width,-height,height,-1000,1000);
	glOrtho(-1, 1, -1, -1, -1, 1);
}

void display(void) //This function is where call other functions and provides display to user.
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear screen

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glTranslatef(sside, 0, -sdepth);
	glRotatef(-stheta, -1, 0, 0);
	glRotatef(sphi, 0, 1, 0);
	glTranslatef(sx, 0, -sy);

	glColor3f(1, 1, 1);

	
	steeringWheel(); //steering Wheel


	wireBox(3.9, 0.7, 1.8);
	constantLine(-1.8, -0.4, 1.45, -1.8, -0.45, -1.4); //Back axle
	constantLine(1.8, -0.4, 1.5, 1.8, -0.45, -1.5); //Front axle
	constantLine(1.8, -0.4, 0, -1.8, -0.45, 0); //Shaft
	constantLine(1.8, -0.4, 0, 1.6, 2.0, 0.1); //Steering column
	
	
	//Back Tires
	drawCircle(-1.8, -0.4, 1.3, 0.5, 360); 
	drawCircle(-1.8, -0.4, -1.3, 0.5, 360); 
	
	frontTireLines1();
	frontTireLines2();
	backTireLines1();
	backTireLines2();
	steeringWheelLine1();
	steeringWheelLine2();

	//Front Tires
	movingCircle1();
	movingCircle2();
	
	glPopMatrix();

	angle -= 5.0f;

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) //This event callback is executed whenever there is a mouse event
{
	mouseX = x; mouseY = y;
	mouse_left_click = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
	glutPostRedisplay();
}


void mouseMove(int x, int y) { //This even callback is executed whenever the mouse is moved
	// rotate
	if (mouse_left_click)
	{
		sphi += (float)(x - mouseX) / 4.0;
		stheta += (float)(mouseY - y) / 4.0;
		// if (stheta<0) stheta=0;
	}
	mouseX = x;
	mouseY = y;
	glutPostRedisplay();
}

void Menu(int value) {

	switch (value)
	{
	case 1:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, 1.0, 1.0, 100.0);
		gluLookAt(2, 7, -4, -1, 1, 5, 0.1, 0.5, 0);
		break;
	
	case 2:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(70.0f, 1.0, 1.0, 10.0);
		gluLookAt(2, 5, 10, 0, 1, 5, 0.1, 0.5, 0);
		break;

	case 3:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0f, 1.0, 1.0, 100.0);
		gluLookAt(-4, 7, 7, -1, 1, 5, 0.1, 0.5, 0);
		break;


	case 4:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(35.0f, 1.0, 1.0, 100.0);
		gluLookAt(4, -10, -4, -1, 1, 5, 0.1, 0.5, 0);
		break;

		break;
	}
}

void main(int argc, char **argv) //Initializes GLUT, the display mode, and main window; 
								//registers callbacks; does application initialization; enters the main event loop.
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("WireCar");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutSpecialFunc(revolve);
	glutTimerFunc(0, timer, 0);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);
	int menu = glutCreateMenu(Menu);
	glutAddMenuEntry("Right", 1);
	glutAddMenuEntry("Left", 2);
	glutAddMenuEntry("Up", 3);
	glutAddMenuEntry("Bottom", 4);
	glutCreateMenu(Menu);
	glutAddSubMenu("View", menu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	init();
	
	glutMainLoop();
}
