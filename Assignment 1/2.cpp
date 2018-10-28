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

struct point
{
	double x,y,z;
};

struct point pos;
struct point v;


void drawBox(){
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(2);
		glBegin(GL_LINES);{
			glVertex3f( 100,100,0);
			glVertex3f(-100,100,0);

			glVertex3f(-100,100,0);
			glVertex3f(-100, -100,0);

			glVertex3f(-100,-100,0);
			glVertex3f(100, -100,0);

			glVertex3f(100, -100,0);
			glVertex3f(100, 100,0);
		}glEnd();
}

void drawArrow(){
    glLineWidth(1.5);
		glBegin(GL_LINES);{
			glVertex3f( pos.x + 5*v.x,pos.y + 5*v.y,0);
			glVertex3f( pos.x - 5*v.x,pos.y - 5*v.y,0);
		}glEnd();

		glColor3f(1.0, 0 , 0);
		glBegin(GL_TRIANGLES);
        {
            glVertex3f( pos.x + 5*v.x,pos.y + 5*v.y,0);
			glVertex3f( pos.x + 2*v.x - 3*v.y ,pos.y + 2*v.y + 3*v.x,0);
			glVertex3f( pos.x + 2*v.x + 3*v.y ,pos.y + 2*v.y - 3*v.x,0);
        }
        glEnd();

}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:
			break;
		case GLUT_KEY_UP:
			break;

		case GLUT_KEY_RIGHT:
			//cameraAngle += 0.03;
			v.x = v.x*cosA + v.y*sinA ;
			v.y = v.y*cosA - v.x*sinA ;
			break;
		case GLUT_KEY_LEFT:
			//cameraAngle -= 0.03;
			v.x = v.x*cosA - v.y*sinA ;
			v.y = v.y*cosA + v.x*sinA ;
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
	gluLookAt(0,0,200,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawBox();
	drawArrow();

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	//codes for any changes in Models, Camera
	{
	    pos.x += 0.03 * v.x ;
	    pos.y += 0.03 * v.y ;
	    if(pos.x >= 100 or pos.x <= -100){
            v.x = -v.x ;
	    }
	    if(pos.y >= 100 or pos.y <= -100){
            v.y = -v.y ;
	    }
	    double temp = pow(v.x*v.x + v.y*v.y, 0.5) ;
	    v.x = v.x * pow(2,0.5) / temp ;
	    v.y = v.y * pow(2,0.5) / temp ;
	}
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	cameraHeight=150.0;
	cameraAngle=1.0;

	{
	    pos.x = 0; pos.y = 0; pos.z = 0;
	    v.x = 1 ; v.y = 1; v.z = 0;
	}

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

	glutCreateWindow("My OpenGL Program");

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
