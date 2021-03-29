#include <stdlib.h>
#include <stdio.h>
#include "../vs/setup.h"

#if _WIN32
# include <windows.h>
#endif
#if __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

const float shipWidth = 8;
const float shipHeight = 10;
const float shipBot = -4;

const float shipX = -80;
const float shipY = -80;


const int shipFill[3] = { 66, 221, 245 };
const int shipOutline[3] = { 14, 0, 143 };

//Draw game rectangle area
void drawGameArea() {
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 255, 0);
    glVertex3f(-95, -95, 0);
    glVertex3f(-95, 95, 0);
    glVertex3f(95, 95, 0);
    glVertex3f(95, -95, 0);
    glEnd();

    testFunc();
}

void drawShip()
{
    glPushMatrix();
    //glRotatef(45, 0, 0, 1);
    //glTranslatef(-5, -5, 0);
    glLineWidth(3);

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0, 0, 255);
    glVertex3f((shipWidth / 2) + shipX, -1*(shipHeight) + shipY, 0); //bot right
    glVertex3f(0 + shipX, shipHeight + shipY, 0); // top middle
    glVertex3f(0 + shipX, shipBot + shipY, 0); // bot middle
    glVertex3f(-1*(shipWidth / 2) + shipX, -1 * (shipHeight) + shipY, 0); // bot left
    glEnd();

        // Draw ship outline
    glBegin(GL_LINE_LOOP);
    glColor3f(255, 0, 0);
    glVertex3f((shipWidth / 2) + shipX, -1 * (shipHeight)+shipY, 0); //bot right
    glVertex3f(0 + shipX, shipHeight + shipY, 0); // top middle
    glVertex3f(-1 * (shipWidth / 2) + shipX, -1 * (shipHeight)+shipY, 0); // bot left
    glVertex3f(0 + shipX, shipBot + shipY, 0); // bot middle
    glEnd();
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glPointSize(5);

    drawGameArea();
    drawShip();

    int err;
    while ((err = glGetError()) != GL_NO_ERROR)
        printf("display: %s\n", gluErrorString(err));

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
    case 'q':
        exit(EXIT_SUCCESS);
        break;
    default:
        break;
    }
}

void init()
{
    /* These OpenGL calls only need to be done once in this sample,
     * but normally they would go elsewhere, e.g. display()
     */
    glMatrixMode(GL_PROJECTION);
    glOrtho(-100, 100, -100, 100, -100, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Asteroid Arena");
    glutFullScreen();

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return(EXIT_SUCCESS);
}


