#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include "bmp.hpp"
#include "../barnes_hut.hpp"
#include "../rw.hpp"
using namespace std;

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*FOR CALCULATIONS*/
body_t bodies[MAX_BODIES_NUMBER];
speed_t speed[MAX_BODIES_NUMBER];
force_t forces[MAX_BODIES_NUMBER];
unsigned int bodies_number;
coord_t space_radius;
duration_t interval;

/*FOR DISPLAYING*/
const double PI = 3.1415926535897932384626433832795;
int side, x_padding, y_padding;
RGBTRIPLE *pixels;
double coord_multyply;

/*Saving current picture to bmp file*/
void save_bitmap( const char *file_name ){
	glReadPixels ( x_padding, y_padding, side, side, GL_RGB, GL_UNSIGNED_BYTE, pixels );
	SaveBitmapToFileColor ( pixels, side, side, 24, file_name );
}

/* GLUT callback Handlers */

static void resize(int width, int height)
{
	side = min ( width, height );
	x_padding = ( width - side ) / 2;
	y_padding = ( height - side ) / 2;
	delete [] pixels;
	pixels = new RGBTRIPLE [ side * side ];

	glViewport(x_padding, y_padding, side, side);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	double z_near = 2.0;
	double z_far = 200.0;
	coord_multyply = z_far / 2.0 / z_near / space_radius;
    glFrustum(-1.1, 1.1, -1.1, 1.1, z_near, z_far);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glTranslated(0.0, 0.0, -z_far/2.0);
}

static void display(void)
{
    //const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    //const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

	for ( unsigned int i = 0; i < bodies_number; ++i ) {
		glPushMatrix();
			glTranslated ( bodies[i].x * coord_multyply, bodies[i].y * coord_multyply, 0.0 );
			glColor3ub ( bodies[i].red, bodies[i].green, bodies[i].blue );
			glutSolidSphere( 1, 32, 32 );
		glPopMatrix();
	}

    glutSwapBuffers();
	save_bitmap("test.bmp");
}


static void key(unsigned char key, int, int)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
			glScaled ( 2, 2, 2 );
            break;

        case '-':
			glScaled ( 0.5, 0.5, 0.5 );
            break;


    }

    glutPostRedisplay();
}

static void idle(void){

	static point_t min_point = { -space_radius, -space_radius }, max_point = { space_radius, space_radius };
    build(bodies, bodies_number, min_point, max_point );
    calculate(bodies, bodies_number, forces, min_point, max_point);
	movement(bodies, bodies_number, forces, speed, interval );

    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
	read_test( argc, argv, bodies_number, space_radius, bodies, speed, interval );

    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Universe");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
