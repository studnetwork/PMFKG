#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <vector>
#include <stdio.h>
#include <math.h>

using namespace glm;
using namespace std;

/*--------------------------------------------------*/

char title[] = "Prozor";
int FPS = 60;
vec3 CameraPosition(25.0, 17.0, 10.0);
vec3 LookAt_vector(0.0, 0.0, 0.0);
vec3 LookUp_vector(0.0, 1.0, 0.0);

vec3 rocketPos(0, 0, 0);

/*--------------------------------------------------*/

vec3 yellow(1.0, 0.9, 0.8);
vec3 grey(0.05, 0.05, 0.03);
vec3 lightgrey(0.3,0.3,0.4);
vec3 white(1.0, 1.0, 1.0);

vec3 orange(1.0, .7, .1);
vec3 darkOrange(.4, .1, .0);
vec3 red(1.0,0.3,0.3);

vec3 lblue(0, .7, 1);

void setColor(vec3 color) {
	glColor3f(color.r, color.g, color.b);
}

vec3 lerp(vec3 a, vec3 b, float t) {
	vec3 v;
	v.x = b.x * t + a.x * (1.0 - t);
	v.y = b.y * t + a.y * (1.0 - t);
	v.z = b.z * t + a.z * (1.0 - t);
	return v;
}

void DrawCylinder(vec3 pos, float radius, float height, int n, vec3 color2, vec3 color1, float xOffset = 0.0, float x2Offset = 0.0) {
	vec3 a(radius + xOffset, 0, 0);
	vec3 b(radius + x2Offset, height, 0);

	vec3 lastA(a), lastB(b);

	float angle = 6.28 / n;
	mat3 rotation = rotate(angle, vec3(0, 1, 0));

	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < n; i++) {
		setColor(lerp(color1, color2, abs((float)i / n - 0.5)));
        //iscrtavanje
		glVertex3f(lastA.x + pos.x, lastA.z + pos.y, lastA.y + pos.z);
		glVertex3f(lastB.x + pos.x, lastB.z + pos.y, lastB.y + pos.z);

		lastA = lastA * rotation;
		lastB = lastB * rotation;
	}
	glVertex3f(a.x + pos.x, a.z + pos.y, a.y + pos.z);
	glVertex3f(b.x + pos.x, b.z + pos.y, b.y + pos.z);
	glEnd();
}

mat3 camRot;
mat3 effectScale;
float effectSpeed, effectT;
mat3 defaultScale = scale(vec3(1, 1, 1));

void animInit() {
	camRot = rotate(-0.005f, vec3(0, 1, 0));

	effectT = 0.0f;
	effectSpeed = 0.2f / 60;
}

void DrawCone(vec3 pos, float radius, float height, int n, vec3 color2, vec3 color1, mat3 scale = defaultScale) {
	vec3 a(radius, 0, 0);
	vec3 b(0, height, 0);

	a = scale * a;
	b = scale * b;

	vec3 lastA(a);

	float angle = 6.28 / n;
	mat3 rotation = rotate(angle, vec3(0, 1, 0));

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < n; i++) {

		setColor(lerp(color1, color2, abs((float)i / n - 0.5)));
		glVertex3f(lastA.x + pos.x, lastA.z + pos.y, lastA.y + pos.z);
		glVertex3f(b.x + pos.x, b.z + pos.y, b.y + pos.z);

		lastA = rotation * lastA;
	}
	glVertex3f(a.x + pos.x, a.y + pos.y, a.z + pos.z);
	glEnd();
}

/*--------------------------------------------------*/

void DrawAxis(void)
{
	glLineWidth(2.0);

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(3.0, 0.0, 0.0);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 3.0, 0.0);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 3.0);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_NONE, GL_LINE);
	glEnable(GL_POLYGON_SMOOTH);

	// DrawAxis();
	setColor(lightgrey);
	glBegin(GL_QUADS);
	glVertex3f(-40.0, -2.0, -40.0);
	glVertex3f(-40.0, -2.0, 40.0);
	glVertex3f(40.0, -2.0, 40.0);
	glVertex3f(40.0, -2.0, -40.0);
	glEnd();

	//Meta
    DrawCylinder(vec3(0.0,5.0,0.0),3.0,1.0,45,orange,darkOrange);
    DrawCone(vec3(0.0,5.0,0.0),3.0,0.0,45,orange,orange);
    //Strelica-------
    DrawCylinder(vec3(0.0,3.0,-15.0),0.35,1.75,45,orange,darkOrange);
    DrawCylinder(vec3(0.0,3.0,-13.2),0.15,0.5,45,red, darkOrange,0.2);
    DrawCylinder(vec3(0.0,3.0,-12.75),0.15,0.7,45,red,darkOrange);
    DrawCone(vec3(0.0,3.0,-12.05),0.15,0.6,45,red,darkOrange);
    DrawCylinder(vec3(0.0,3.0,-15.4),0.2,0.4,45,red, darkOrange,0.0,0.15);
    DrawCylinder(vec3(0.0,3.0,-16.97),0.2,1.6,45,red,darkOrange);
    DrawCylinder(vec3(0.0,3.0,-17.6),0.0,0.6,45,orange,darkOrange, 0.0, 0.2);

    //trouglici na stelici
    setColor(orange);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0,3.0,-16.97);
    glVertex3f(0.0,4.0,-19.0);
    glVertex3f(0.0,2.0,-19.0);
    setColor(darkOrange);
    glVertex3f(0.0,3.0,-16.97);
    glVertex3f(1.0,3.0,-19.0);
    glVertex3f(-1.0,3.0,-19.0);
    glEnd();

	glutSwapBuffers();
}

void timer(int v)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// rocketPos.y += 0.05;
	CameraPosition = camRot * CameraPosition;
	CameraPosition.y = rocketPos.y + 7.0;

	gluLookAt(
		CameraPosition.x+4.0, CameraPosition.y, CameraPosition.z,
		rocketPos.x, rocketPos.y + 5.0, rocketPos.z,		//LookAt_vector.x, LookAt_vector.y, LookAt_vector.z,
		LookUp_vector.x, LookUp_vector.y, LookUp_vector.z
	);

	effectT += effectSpeed;
	float t = clamp(effectT, 0.0f, 1.0f);
	//printf("%f\n", t);
	effectScale = scale(lerp(vec3(0.7, 0.1, 0.7), vec3(1.1, 4.5, 1.1), t));

	glutTimerFunc(1000 / FPS, timer, v);
	glutPostRedisplay();
}

void reshape(GLsizei width, GLsizei height)
{
	if (height == 0)
	{
		height = 1;
	}

	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0f, aspect, 0.1f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		CameraPosition.x+4.0, CameraPosition.y, CameraPosition.z,
		LookAt_vector.x, LookAt_vector.y, LookAt_vector.z,
		LookUp_vector.x, LookUp_vector.y, LookUp_vector.z
	);
}

void initGL(void)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SMOOTH);

	animInit();
}

void mousePress(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			//FUNKCIJA
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			//FUNKCIJA
		}
		break;
	default:
		break;
	}
}

void keyPress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'A':
	case 'a':
		//FUNCTION
		break;
	case 'S':
	case 's':
		//FUNCTION
		break;
	case 'D':
	case 'd':
		//FUNCTION
		break;
	case 'W':
	case 'w':
		//FUNCTION
		break;
	default:
		break;
	}
}

/*--------------------------------------------------*/

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(950, 650);
	glutInitWindowPosition(150, 50);
	glutCreateWindow(title);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		CameraPosition.x+4.0, CameraPosition.y, CameraPosition.z,
		LookAt_vector.x, LookAt_vector.y, LookAt_vector.z,
		LookUp_vector.x, LookUp_vector.y, LookUp_vector.z
	);


	glutDisplayFunc(display);
	glutTimerFunc(100, timer, 0);
	glutReshapeFunc(reshape);

	initGL();

	glutMouseFunc(mousePress);
	glutKeyboardFunc(keyPress);

	glutMainLoop();

	return 0;
}
