#include <GL/freeglut.h>	
#include <vector>		

#include <glm/vec3.hpp> //glm Vector3D
#include <glm/mat3x3.hpp> //glm Matrix3x3
	
using namespace std;
using namespace glm;
	
double w = 2.0; // angular velocity 	
int FPS = 60; // frames per sec 	
double alpha = w/FPS ;	
	
vector<vec3> kvadrat;	

mat3 MT;
	
void CreateSquare() 	
{	
	kvadrat.resize(4);	
	kvadrat[0] = vec3(1.0, 1.0, 1.0);	
	kvadrat[1] = vec3(2.0, 1.0, 1.0);	
	kvadrat[2] = vec3(2.0, 2.0, 1.0);	
	kvadrat[3] = vec3(1.0, 2.0, 1.0);	
}	
	
void CreateTransformMatrix(mat3 &MT)	
{	
	mat3 MTranslateАО{1, 0, -1,
					  0, 1, -1,
					  0, 0, 1 },
		 MTranslateОА{1, 0, 1,
					  0, 1, 1,
					  0, 0, 1 },
         MRotate{cos(alpha), -sin(alpha), 0,
					  sin(alpha), cos(alpha), 0,
					  0, 0, 1 };

	MT =  MTranslateАО * MRotate * MTranslateОА;
}	
	
void Transform(mat3 &M, vector<vec3> &v)	
{	
	for (int i = 0; i < v.size(); i++)	v[i] = v[i] * M;	
}	
	
void DrawPolygon(vector<vec3> v)	
{	
	glBegin(GL_POLYGON);	
	for (int i = 0; i < v.size(); i++)	glVertex3f(v[i].x, v[i].y, 0);	
	glEnd();	
}	
	
	
void display(void)	
{		
	glClear(GL_COLOR_BUFFER_BIT);	
	DrawPolygon(kvadrat);	
	glFlush();	
}	
	
	
void timer(int v)	
{	     	
	Transform(MT, kvadrat);	
	glutTimerFunc(1000/FPS,timer,v);	
	glutPostRedisplay();	
}	
	
void init()	
{	
	glClearColor(0.0, 0.0, 0.0, 0.0);	
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();	
	glOrtho(0.0, 3.0, 0.0, 3.0, -1.0, 1.0);	
}	
	
int main(int argc, char** argv) {	
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	
	glutInitWindowSize(500, 500);	
	glutInitWindowPosition(100, 100);	
	glutCreateWindow("hello");	
	init();	
	
	CreateSquare();	
	CreateTransformMatrix(MT);	
	
	glutDisplayFunc(display);	
	glutTimerFunc(100, timer, 0);	
	glutMainLoop();	
	
	return 0;	
}