//kod pisan na Windows operativnom sistemu, treba da se prepravi za linux
#include<windows.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>

float sunx = -12.0;
float suny = 0.0;
float xprop1 = -4.0;
float yprop1 = -3.0;
float xprop2 = -2.0;
float yprop2 = -2.45 + sqrt(8);

void display();
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}
void reshape(int, int);
void timer(int);

void drawSun() {
    float vert;
    glBegin(GL_POLYGON);
    glColor3f(1.0,1.0,0.0);
    for (int i = 0; i < 360; i++) {
        vert = i * 3.142 / 180;
        glVertex2f(cos(vert)+sunx, sin(vert)+suny);
    }
    glEnd();
}
void drawVetStab() {
    glBegin(GL_POLYGON);
    glColor3f(0.7,0.3,0.0);
    glVertex2f(0.0,-3.0);
    glVertex2f(-2.0,-10.0);
    glVertex2f(2.0,-10.0);
    glEnd();
}
void drawPropellers(float xj, float yj, float xd, float yd) {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0, -3.0);
    glVertex2f(xj, yj);
    glVertex2f(xd, yd);
    glEnd();
}

boolean  mouse_flag;
void mousePress(int button, int state, int x, int y)
{
    
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) mouse_flag = true;
        if (state == GLUT_UP) mouse_flag = false;
        break;
    default:
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(200,200);
    glutCreateWindow("hello");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mousePress);
    glutTimerFunc(0,timer,0);
    
    
    glutMainLoop();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawVetStab();
    drawSun();
    drawPropellers(xprop1, yprop1, xprop2, yprop2);
    drawPropellers(cos(2 * 3.14 / 3) * xprop1 - (yprop1 + 3.0) * sin(2 * 3.14 / 3), (yprop1 + 3.0) * cos(2 * 3.14 / 3) + sin(2 * 3.14 / 3) * xprop1 - 3.0, cos(2 * 3.14 / 3) * xprop2 - (yprop2 + 3.0) * sin(2 * 3.14 / 3), (yprop2 + 3.0) * cos(2 * 3.14 / 3) + sin(2 * 3.14 / 3) * xprop2 - 3.0);
    drawPropellers(cos(4 * 3.14 / 3) * xprop1 - (yprop1 + 3.0) * sin(4 * 3.14 / 3), (yprop1 + 3.0) * cos(4 * 3.14 / 3) + sin(4 * 3.14 / 3) * xprop1 - 3.0, cos(4 * 3.14 / 3) * xprop2 - (yprop2 + 3.0) * sin(4 * 3.14 / 3), (yprop2 + 3.0) * cos(4 * 3.14 / 3) + sin(4 * 3.14 / 3) * xprop2 - 3.0);
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);

}

void timer(int a) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
   // sunx += 0.15;
   // suny = sqrt(100 - sunx*sunx);
    xprop1 = cos(3.14 / 180) * xprop1 - (yprop1 + 3.0) * sin(3.14 / 180);
    xprop2 = cos(3.14 / 180) * xprop2 - (yprop2 + 3.0) * sin(3.14 / 180);
    yprop1 = (yprop1 + 3.0) * cos(3.14 / 180) + sin(3.14 / 180) * xprop1 - 3.0;
    yprop2 = (yprop2 + 3.0) * cos(3.14 / 180) + sin(3.14 / 180) * xprop2 - 3.0;
    if (sunx > 10.0) { sunx = -12.0; }

    if (mouse_flag) {
        sunx += 0.15;
        suny = sqrt(100 - sunx*sunx);
        xprop1 = cos(3.14 / 180) * xprop1 - (yprop1 + 3.0) * sin(3.14 / 180);
        xprop2 = cos(3.14 / 180) * xprop2 - (yprop2 + 3.0) * sin(3.14 / 180);
        yprop1 = (yprop1 + 3.0) * cos(3.14 / 180) + sin(3.14 / 180) * xprop1 - 3.0;
        yprop2 = (yprop2 + 3.0) * cos(3.14 / 180) + sin(3.14 / 180) * xprop2 - 3.0;
        if (sunx > 10.0) { sunx = -12.0; }
    }
}
