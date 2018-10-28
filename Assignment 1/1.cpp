#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

#define cosA 0.99863
#define sinA 0.05234
#define sizeOfObject 20

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double objectSize;

struct point
{
	double x,y,z;
};

struct point cameraPos;
struct point u,r,l;

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


void drawSquare(double a)
{
    glColor3f(1,1,1);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,0);
		glVertex3f( a,-a,0);
		glVertex3f(-a,-a,0);
		glVertex3f(-a, a,0);
	}glEnd();
}


void quarterCylinder(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*pi/2);
        points[i].y=radius*sin(((double)i/(double)segments)*pi/2);
    }
    //draw triangles using generated points
    glColor3f(0,1,0);
    for(i=0;i<segments;i++)
    {
        glBegin(GL_QUADS);
        {
            //glVertex3f(0,0,height);
			glVertex3f(points[i].x,points[i].y,-height/2);
			glVertex3f(points[i+1].x,points[i+1].y,-height/2);
			glVertex3f(points[i+1].x,points[i+1].y,height/2);
			glVertex3f(points[i].x,points[i].y,height/2);
        }
        glEnd();
    }
}


void quarterSphere(double radius,int slices,int stacks)
{
    struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));

		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*pi/2);
			points[i][j].y=r*sin(((double)j/(double)slices)*pi/2);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	glColor3f(1,0,0);
	for(i=0;i<stacks;i++)
	{
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
			}glEnd();
		}
	}
}


void drawCube(double a)
{
    glTranslatef(0,0,20);
    drawSquare(a);
    glTranslatef(0,0,-40);
    drawSquare(a);
    glTranslatef(0,0,20);

    glTranslatef(20,0,0);
    glRotatef(90,0,1,0);
    drawSquare(a);
    glRotatef(-90,0,1,0);

    glTranslatef(-40,0,0);
    glRotatef(90,0,1,0);
    drawSquare(a);
    glRotatef(-90,0,1,0);
    glTranslatef(20,0,0);

    glTranslatef(0,-20,0);
    glRotatef(90,1,0,0);
    drawSquare(a);
    glRotatef(-90,1,0,0);

    glTranslatef(0,40,0);
    glRotatef(90,1,0,0);
    drawSquare(a);
    glRotatef(-90,1,0,0);
    glTranslatef(0,-20,0);
}

void drawFullSphere(double rad){
    double temp = sizeOfObject-rad ;  //center of Sphere

    //upper half
    glTranslatef(temp,temp,temp);
    quarterSphere(rad,24,20);
    glTranslatef(-temp,-temp,-temp);

    glTranslatef(-temp,temp,temp);
    glRotatef(90,0,0,1);
    quarterSphere(rad,24,20);
    glRotatef(-90,0,0,1);
    glTranslatef(temp,-temp,-temp);

    glTranslatef(-temp,-temp,temp);
    glRotatef(180,0,0,1);
    quarterSphere(rad,24,20);
    glRotatef(-180,0,0,1);
    glTranslatef(temp,temp,-temp);

    glTranslatef(temp,-temp,temp);
    glRotatef(270,0,0,1);
    quarterSphere(rad,24,20);
    glRotatef(-270,0,0,1);
    glTranslatef(-temp,temp,-temp);

    //lower half
    glTranslatef(temp,temp,-temp);
    glRotatef(90,0,1,0);
    quarterSphere(rad,24,20);
    glRotatef(-90,0,1,0);
    glTranslatef(-temp,-temp,temp);

    glTranslatef(-temp,temp,-temp);
    glRotatef(90,0,0,1);
    glRotatef(90,0,1,0);
    quarterSphere(rad,24,20);
    glRotatef(-90,0,1,0);
    glRotatef(-90,0,0,1);
    glTranslatef(temp,-temp,temp);

    glTranslatef(-temp,-temp,-temp);
    glRotatef(180,0,0,1);
    glRotatef(90,0,1,0);
    quarterSphere(rad,24,20);
    glRotatef(-90,0,1,0);
    glRotatef(-180,0,0,1);
    glTranslatef(temp,temp,temp);

    glTranslatef(temp,-temp,-temp);
    glRotatef(270,0,0,1);
    glRotatef(90,0,1,0);
    quarterSphere(rad,24,20);
    glRotatef(-90,0,1,0);
    glRotatef(-270,0,0,1);
    glTranslatef(-temp,temp,temp);
}

void drawFullCylinder(double rad){
    double temp = sizeOfObject-rad ;  //center of Sphere

    //first half
    glTranslatef(temp,temp,0);
    quarterCylinder(rad,2*temp,48) ;
    ///quarterCylinder(rad,rad,48) ;
    glTranslatef(-temp,-temp,0);

    glTranslatef(-temp,temp,0);
    glRotatef(90,0,0,1);
    quarterCylinder(rad,2*temp,48) ;
    ///quarterCylinder(rad,rad,48) ;
    glRotatef(-90,0,0,1);
    glTranslatef(temp,-temp,0);

    glTranslatef(-temp,-temp,0);
    glRotatef(180,0,0,1);
    quarterCylinder(rad,2*temp,48) ;
    ///quarterCylinder(rad,rad,48) ;
    glRotatef(-180,0,0,1);
    glTranslatef(temp,temp,0);

    glTranslatef(temp,-temp,0);
    glRotatef(270,0,0,1);
    quarterCylinder(rad,2*temp,48) ;
    ///quarterCylinder(rad,rad,48) ;
    glRotatef(-270,0,0,1);
    glTranslatef(-temp,temp,0);



    //second half
    glTranslatef(0,temp,-temp);
    glRotatef(90,0,1,0);
    quarterCylinder(rad,2*temp,48) ;
    ///quarterCylinder(rad,rad,48) ;
    glRotatef(-90,0,1,0);
    glTranslatef(0,-temp,temp);

    glTranslatef(0,temp,temp);
    glRotatef(90,1,0,0);
    glRotatef(90,0,1,0);
    quarterCylinder(rad,2*temp,48) ;
    //quarterCylinder(rad,rad,48) ;
    glRotatef(-90,0,1,0);
    glRotatef(-90,1,0,0);
    glTranslatef(0,-temp,-temp);

    glTranslatef(0,-temp,temp);
    glRotatef(180,1,0,0);
    glRotatef(90,0,1,0);
    quarterCylinder(rad,2*temp,48) ;
    ///quarterCylinder(rad,rad,48) ;
    glRotatef(-90,0,1,0);
    glRotatef(-180,1,0,0);
    glTranslatef(0,temp,-temp);

    glTranslatef(0,-temp,-temp);
    glRotatef(270,1,0,0);
    glRotatef(90,0,1,0);
    quarterCylinder(rad,2*temp,48) ;
    ///quarterCylinder(rad,rad,48) ;
    glRotatef(-90,0,1,0);
    glRotatef(-270,1,0,0);
    glTranslatef(0,temp,temp);

    //last half
    glTranslatef(temp,0,temp);
    glRotatef(90,1,0,0);
    quarterCylinder(rad,2*temp,48) ;
    ///quarterCylinder(rad,rad,48) ;
    glRotatef(-90,1,0,0);
    glTranslatef(-temp,0,-temp);

    glTranslatef(temp,0,-temp);
    glRotatef(90,0,1,0);
    glRotatef(90,1,0,0);
    quarterCylinder(rad,2*temp,48) ;
    ///quarterCylinder(rad,rad,48) ;
    glRotatef(-90,1,0,0);
    glRotatef(-90,0,1,0);
    glTranslatef(-temp,0,temp);

    glTranslatef(-temp,0,-temp);
    glRotatef(180,0,1,0);
    glRotatef(90,1,0,0);
    quarterCylinder(rad,2*temp,48) ;
    ///quarterCylinder(rad,rad,48) ;
    glRotatef(-90,1,0,0);
    glRotatef(-180,0,1,0);
    glTranslatef(temp,0,temp);

    glTranslatef(-temp,0,temp);
    glRotatef(270,0,1,0);
    glRotatef(90,1,0,0);
    quarterCylinder(rad,2*temp,48) ;
    ///quarterCylinder(rad,rad,48) ;
    glRotatef(-90,1,0,0);
    glRotatef(-270,0,1,0);
    glTranslatef(temp,0,-temp);
}

void keyboardListener(unsigned char key, int x,int y){
    struct point temp;
    double ampt ;
	switch(key){
	    case '1':
            temp.x = r.x ; temp.y = r.y ; temp.z = r.z ;
			r.x = r.x*cosA + l.x*sinA ;
			r.y = r.y*cosA + l.y*sinA ;
			r.z = r.z*cosA + l.z*sinA ;
			ampt = pow(r.x*r.x+r.y*r.y+r.z*r.z, 0.5);
			r.x = r.x/ampt ;
			r.y = r.y/ampt ;
			r.z = r.z/ampt ;

			l.x = l.x*cosA - temp.x*sinA ;
			l.y = l.y*cosA - temp.y*sinA ;
			l.z = l.z*cosA - temp.z*sinA ;
			ampt = pow(l.x*l.x+l.y*l.y+l.z*l.z, 0.5);
			l.x = l.x/ampt ;
			l.y = l.y/ampt ;
			l.z = l.z/ampt ;
			break;
		case '2':
			temp.x = r.x ; temp.y = r.y ; temp.z = r.z ;
			r.x = r.x*cosA - l.x*sinA ;
			r.y = r.y*cosA - l.y*sinA ;
			r.z = r.z*cosA - l.z*sinA ;
			ampt = pow(r.x*r.x+r.y*r.y+r.z*r.z, 0.5);
			r.x = r.x/ampt ;
			r.y = r.y/ampt ;
			r.z = r.z/ampt ;

			l.x = l.x*cosA + temp.x*sinA ;
			l.y = l.y*cosA + temp.y*sinA ;
			l.z = l.z*cosA + temp.z*sinA ;
			ampt = pow(l.x*l.x+l.y*l.y+l.z*l.z, 0.5);
			l.x = l.x/ampt ;
			l.y = l.y/ampt ;
			l.z = l.z/ampt ;
			break;
        case '4':
			temp.x = l.x ; temp.y = l.y ; temp.z = l.z ;
			l.x = l.x*cosA - u.x*sinA ;
			l.y = l.y*cosA - u.y*sinA ;
			l.z = l.z*cosA - u.z*sinA ;
			ampt = pow(l.x*l.x+l.y*l.y+l.z*l.z, 0.5);
			l.x = l.x/ampt ;
			l.y = l.y/ampt ;
			l.z = l.z/ampt ;

			u.x = u.x*cosA + temp.x*sinA ;
			u.y = u.y*cosA + temp.y*sinA ;
			u.z = u.z*cosA + temp.z*sinA ;
			ampt = pow(u.x*u.x+u.y*u.y+u.z*u.z, 0.5);
			u.x = u.x/ampt ;
			u.y = u.y/ampt ;
			u.z = u.z/ampt ;
			break;
        case '3':
			temp.x = l.x ; temp.y = l.y ; temp.z = l.z ;
			l.x = l.x*cosA + u.x*sinA ;
			l.y = l.y*cosA + u.y*sinA ;
			l.z = l.z*cosA + u.z*sinA ;
			ampt = pow(l.x*l.x+l.y*l.y+l.z*l.z, 0.5);
			l.x = l.x/ampt ;
			l.y = l.y/ampt ;
			l.z = l.z/ampt ;

			u.x = u.x*cosA - temp.x*sinA ;
			u.y = u.y*cosA - temp.y*sinA ;
			u.z = u.z*cosA - temp.z*sinA ;
			ampt = pow(u.x*u.x+u.y*u.y+u.z*u.z, 0.5);
			u.x = u.x/ampt ;
			u.y = u.y/ampt ;
			u.z = u.z/ampt ;
			break;
        case '5':
			temp.x = u.x ; temp.y = u.y ; temp.z = u.z ;
			u.x = u.x*cosA + r.x*sinA ;
			u.y = u.y*cosA + r.y*sinA ;
			u.z = u.z*cosA + r.z*sinA ;
			ampt = pow(u.x*u.x+u.y*u.y+u.z*u.z, 0.5);
			u.x = u.x/ampt ;
			u.y = u.y/ampt ;
			u.z = u.z/ampt ;

			r.x = r.x*cosA - temp.x*sinA ;
			r.y = r.y*cosA - temp.y*sinA ;
			r.z = r.z*cosA - temp.z*sinA ;
			ampt = pow(r.x*r.x+r.y*r.y+r.z*r.z, 0.5);
			r.x = r.x/ampt ;
			r.y = r.y/ampt ;
			r.z = r.z/ampt ;
			break;
        case '6':
			temp.x = u.x ; temp.y = u.y ; temp.z = u.z ;
			u.x = u.x*cosA - r.x*sinA ;
			u.y = u.y*cosA - r.y*sinA ;
			u.z = u.z*cosA - r.z*sinA ;
			ampt = pow(u.x*u.x+u.y*u.y+u.z*u.z, 0.5);
			u.x = u.x/ampt ;
			u.y = u.y/ampt ;
			u.z = u.z/ampt ;

			r.x = r.x*cosA + temp.x*sinA ;
			r.y = r.y*cosA + temp.y*sinA ;
			r.z = r.z*cosA + temp.z*sinA ;
			ampt = pow(r.x*r.x+r.y*r.y+r.z*r.z, 0.5);
			r.x = r.x/ampt ;
			r.y = r.y/ampt ;
			r.z = r.z/ampt ;
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			//cameraHeight -= 3.0;
			cameraPos.x -= 2 * l.x ;
			cameraPos.y -= 2 * l.y ;
			cameraPos.z -= 2 * l.z ;
			break;
		case GLUT_KEY_UP:		// up arrow key
			//cameraHeight += 3.0;
			cameraPos.x += 2 * l.x ;
			cameraPos.y += 2 * l.y ;
			cameraPos.z += 2 * l.z ;
			break;

		case GLUT_KEY_RIGHT:
			//cameraAngle += 0.03;
			cameraPos.x += 2 * r.x ;
			cameraPos.y += 2 * r.y ;
			cameraPos.z += 2 * r.z ;
			break;
		case GLUT_KEY_LEFT:
			//cameraAngle -= 0.03;
			cameraPos.x -= 2 * r.x ;
			cameraPos.y -= 2 * r.y ;
			cameraPos.z -= 2 * r.z ;
			break;

		case GLUT_KEY_PAGE_UP:
		    cameraPos.x += 2 * u.x ;
			cameraPos.y += 2 * u.y ;
			cameraPos.z += 2 * u.z ;
			break;
		case GLUT_KEY_PAGE_DOWN:
		    cameraPos.x -= 2 * u.x ;
			cameraPos.y -= 2 * u.y ;
			cameraPos.z -= 2 * u.z ;
			break;

		case GLUT_KEY_INSERT:
			break;
		case GLUT_KEY_HOME:
		    if(objectSize > 0) objectSize -= 1 ;
			break;
		case GLUT_KEY_END:
		    if(objectSize < 20) objectSize += 1 ;
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

	///clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	///load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

    //now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	gluLookAt(cameraPos.x,cameraPos.y,cameraPos.z,	cameraPos.x+10*l.x,cameraPos.y+10*l.y,cameraPos.z+10*l.z,	u.x,u.y,u.z);
	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();

	drawCube(objectSize);
	drawFullSphere(sizeOfObject-objectSize);
    drawFullCylinder(sizeOfObject-objectSize);

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=1;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	objectSize = sizeOfObject/2;

    ///Camera initial position
    {
        cameraPos.x = 100;
        cameraPos.y = 100;
        cameraPos.z = 0;
    }
    ///set 3d vectors
    {
        double temp = 1 / pow(2,0.5);
        u.x = 0 ; u.y = 0 ; u.z = 1 ;
        r.x = -temp ; r.y = temp ; r.z = 0 ;
        l.x = -temp ; l.y = -temp ; l.z = 0 ;
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
