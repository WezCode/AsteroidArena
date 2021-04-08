#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Ship.h"
#include "Input.h"
#include "GameEngine.h"
#include "Arena.h"

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

Ship* ship;
Input* input;
GameEngine* ge;
Arena* arena;

float g_last_time = 0.0;
int screenWidth = 0;
int screenHeight = 0;


void drawLine(Point a, Point b, Color c) {

    printf("drawing line a: (%f,%f) b: (%f,%f) c: (%d,%d,%d) \n", a.x, a.y, b.x, b.y, c.r, c.g, c.b);
    glBegin(GL_LINES);
    glColor3f(c.r, c.g, c.b);
    glVertex3f(a.x, a.y, 0);
    glVertex3f(b.x, b.y, 0);
    glEnd();
}

//Draw game rectangle area 
void drawGameArena() {

    Line topWall = ge->getTopWall();
    Line botWall = ge->getBotWall();
    Line leftWall = ge->getLeftWall();
    Line rightWall = ge->getRightWall();

    drawLine(topWall.a, topWall.b, topWall.c);
    drawLine(botWall.a, botWall.b, botWall.c);
    drawLine(leftWall.a, leftWall.b, leftWall.c);
    drawLine(rightWall.a, rightWall.b, rightWall.c);

}

void drawShip(int height, int width, float x, float y, int rotation)
{
    glPushMatrix();
    glTranslatef(x, y - shipCentreOffset, 0);
    glRotatef(rotation, 0, 0, 1);
    glTranslatef(-x, -(y - shipCentreOffset), 0);

    // Draw ship outline
    glBegin(GL_LINE_LOOP);
    glColor3f(255, 0, 0); 
    glVertex3f(x + width / 2, y - height / 2, 0); //bot right
    glVertex3f(x, y + height / 2, 0); // top middle
    glVertex3f(x - width / 2, y - height / 2, 0); // bot left
    glVertex3f(x, y - height / 4, 0); // bot middle
    glEnd();

    //Draw ship fill
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0, 0, 255);
    glVertex3f(x + width / 2, y - height / 2, 0); //bot right
    glVertex3f(x, y + height / 2, 0); // top middle
    glVertex3f(x, y - height / 4, 0); // bot middle
    glVertex3f(x - width / 2, y - height / 2, 0); // bot left
    glEnd();

    glPopMatrix();
}

void drawShipCircle(float radius)
{
    float twoPi = 2.0 * 3.14159265;
    int number = 40;

    float shipX = ship->getShipX();
    float shipY = ship->getShipY();

    glBegin(GL_LINE_STRIP);
    glColor3f(255, 0, 0);
    
    for (int i = 0; i <= number; ++i) {
        glVertex3f(shipX + radius * cos(i * twoPi / number), shipY - shipCentreOffset + radius * sin(i * twoPi / number), 1);
    }

    Point top = { shipX, shipY - shipCentreOffset + radius};
    Point left = { shipX - radius, shipY};
    Point bot = { shipX, shipY - shipCentreOffset - radius };
    Point right = { shipX + radius, shipY };

    glEnd();

}

void display()
{
    //printf("display \n");

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glPointSize(5);

    drawGameArena();
    drawShip(ship->getShipHeight(), ship->getShipWidth(), ship->getShipX(), ship->getShipY(), ship->getRotation());

    //Draw small circle
    drawShipCircle(ship->getShipWidth() / 1.6);
    //Draw big circle
    drawShipCircle(100);

    int err;
    while ((err = glGetError()) != GL_NO_ERROR)
        printf("display: %s\n", gluErrorString(err));

    glutSwapBuffers();
}

void onKeyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
    case 'q':
        exit(EXIT_SUCCESS);
        break;
    case 'a':
        input->setKeyPressed(Key::A, true);
        break;
    case 'w':
        input->setKeyPressed(Key::W, true);
        break;
    case 'd':
        printf("D key pressed");
        input->setKeyPressed(Key::D, true);
        break;
    default:
        break;
    }
}

void onKeyRelease(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        //printf("W key released");
        input->setKeyPressed(Key::W, false);
        break;
    case 'a':
        //printf("A key released");
        input->setKeyPressed(Key::A, false);
        break;
    case 'd':
        //printf("D key released");
        input->setKeyPressed(Key::D, false);
        break;
    default:
        break;
    }
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glOrtho(-gameOrthoWidth / 2, gameOrthoWidth / 2, -gameOrthoHeight / 2, gameOrthoHeight / 2, -1, 1);
}


void updateShipState(float dt)
{

    int currentRotation = ship->getRotation();
    //printf("in update ship state");
    //Rotate Left
    if (input->getKeyPressed(Key::A)) {
        ship->setRotation(currentRotation + dt * 200);
    }
    //Rotate right
    if (input->getKeyPressed(Key::D)) {
        ship->setRotation(currentRotation - dt * 200);
    }
    //Move forward
    if (input->getKeyPressed(Key::W)) {
        ship->moveFoward(dt);
    }

}

// Update various game objects
void updateGameState(float dt)
{
    ge->checkShipWallWarning(ship, 150, ship->getShipWidth() / 1.6);
    //ge->checkShipWallCollision(ship, ship->getShipWidth() / 1.6);

}


void onIdle()
{
    float cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    float dt = cur_time - g_last_time;

    //printf("dt %f", dt);

    updateShipState(dt);
    updateGameState(dt);

    g_last_time = cur_time;
    glutPostRedisplay();
}

void onReshape(int w, int h)
{
    screenWidth = w;
    screenHeight = h;

    //printf("window width %d ", screenWidth);
    //printf("window height %d \n", screenHeight);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Asteroid Arena");
    glutFullScreen();
    //glutReshapeFunc(onReshape);

    init();

    //Create Ship Object
    ship = new Ship();
    input = new Input();
    arena = new Arena();
    ge = new GameEngine();

    glutDisplayFunc(display);
    glutKeyboardFunc(onKeyPress);
    glutKeyboardUpFunc(onKeyRelease);
    glutIdleFunc(onIdle);

    glutMainLoop();
    return(EXIT_SUCCESS);
}


