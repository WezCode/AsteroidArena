#pragma once
#include "Ship.h"
#ifndef GameEngine_H
#define GameEngine_H

typedef struct Point {
	float x, y;
} Point;

typedef struct Color {
	int r, g, b;
};

typedef struct Line {
	Point a, b;
	Color c;
} Line;

const Color green = { 0, 255, 0 };
const Color red = { 255, 0, 0 };

const int gameOrthoWidth = 1920;
const int gameOrthoHeight = 1080;

class GameEngine {
	/*static GameEngine* instance;*/


public:
	//static GameEngine* getInstance();
	GameEngine();

	//Check ship approaching wall
	void checkShipWallWarning(Ship* ship, int bigRadius, int smallRadius);

	//Checks if ship has collided with wall
	void checkShipWallCollision (Ship* ship, int radius);

	//Checks if asteroid has collided with asteroid or wall
	bool checkAsteroidCollision();

	Line getTopWall();
	Line getBotWall();
	Line getLeftWall();
	Line getRightWall();



private:
	//Line topWall = { Point { -940, 520 }, Point { 940, 520 }, green };
	//Line botWall = { Point { -940, -520 }, Point { 940, -520 }, green };
	//Line leftWall = { Point { -940, -520 }, Point { -940, 520 }, green };
	//Line rightWall = { Point { 940, -520 }, Point { 940, 520 }, green };

	Line topWall;
	Line botWall;
	Line leftWall;
	Line rightWall;

};


#endif