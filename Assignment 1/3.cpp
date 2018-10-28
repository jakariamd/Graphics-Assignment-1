#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))
#define cosA 0.99863
#define sinA 0.05234

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
double forarmAngle;
double bisapAngle;
double handAngle;
double finAngele;
double thumbAngle;

struct point
{
	double x,y,z;
};

void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}

void drawArm()
{
    glRotatef(angle,1,0,0);
    glRotatef(bisapAngle,0,1,0);
    glScalef(1,1,5);
    glTranslatef(0,0,-5);
    glutWireSphere (5, 10, 20);
    glTranslatef(0,0,5);
    glScalef(1,1,1.0/5);

    glTranslatef(0,0,-50);
    glRotatef(forarmAngle,1,0,0);
    glScalef(1,1,5);
    glTranslatef(0,0,-3);
    glutWireSphere (3, 6, 12);
    glTranslatef(0,0,-3);
    glScalef(1,1,1.0/5);

    glRotatef(handAngle,0,0,1);
    glBegin(GL_TRIANGLES);{
            glVertex3f(0,0,0);
			glVertex3f(5,0,-10);
			glVertex3f(-5,0,-10);
    }glEnd();
    glTranslatef(0,0,-10);

    glTranslatef(5,0,0);
    glRotatef(thumbAngle,1,0,0);
    glScalef(1,1,2);
    glTranslatef(0,0,-2);
    glutWireSphere (2, 4, 8);
    glTranslatef(0,0,2);
    glScalef(1,1,1.0/2);
    glRotatef(-thumbAngle,1,0,0);

    glTranslatef(-10,0,0);
    glRotatef(finAngele,0,0,1);
    glScalef(1,1,2);
    glTranslatef(0,0,-2);
    glutWireSphere (2, 4, 8);
}


void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
		    if(angle > -45) angle -= 3;
			break;
		case '2':
		    if(angle < 45) angle += 3;
			break;
        case '3':
		    if(forarmAngle > -90) forarmAngle -= 3;
			break;
		case '4':
		    if(forarmAngle < 0) forarmAngle += 3;
			break;
        case '5':
		    if(handAngle < 45) handAngle += 3;
			break;
		case '6':
		    if(handAngle > -45) handAngle -= 3;
			break;
		case '7':
		    if(finAngele < 90) finAngele += 3;
			break;
		case '8':
		    if(finAngele > 0) finAngele -= 3;
			break;
        case '9':
            if(thumbAngle > -90) thumbAngle -= 3;
			break;
		case '0':
		    if(thumbAngle < 0) thumbAngle += 3;
			break;
		case 'q':
		    if(bisapAngle < 90) bisapAngle += 3;
			break;
		case 'w':
		    if(bisapAngle > 0) bisapAngle -= 3;
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraHeight -= 3.0;
			break;
		case GLUT_KEY_UP:		// up arrow key
			cameraHeight += 3.0;
			break;

		case GLUT_KEY_RIGHT:
			cameraAngle += 0.03;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle -= 0.03;
			break;

		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}



void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	gluLookAt(110*cos(cameraAngle), 110*sin(cameraAngle), cameraHeight,		0,0,-50,		0,0,1);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawArm();

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	//angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=-50.0;
	cameraAngle=0.6;
	angle=0;
	forarmAngle = 0;
	bisapAngle = 0;
	handAngle = 0;
	finAngele = 0;
	thumbAngle = 0;

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Robot Arm");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
