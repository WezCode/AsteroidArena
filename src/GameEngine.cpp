#include "GameEngine.h"
#include <stdio.h>

// Singleton pattern, returns pointer to GameEngine instance
//GameEngine* GameEngine::getInstance() {
//	if (!instance)
//		instance = new GameEngine;
//	return instance;
//}

GameEngine::GameEngine() {
	topWall = { Point { -940.f, 520.f }, Point { 940.f, 520.f }, green };
	botWall = { Point { -940, -520 }, Point { 940, -520 }, green };
	leftWall = { Point { -940.f, -520.f }, Point { -940.f, 520.f }, green };
	rightWall = { Point { 940.f, -520.f }, Point { 940.f, 520.f }, green };
}

//Check if large bounding circle of ship collides with any walls
void GameEngine::checkShipWallWarning(Ship* ship, int bigRadius, int smallRadius) {

	////
	if (topWall.a.y <= ship->getShipY() + bigRadius) {
		topWall.c = red;
		if (topWall.a.y <= ship->getShipY() + smallRadius) {
			ship->resetShipValues();
			return;
		}
	} else {
		topWall.c = green;
	}
	if (leftWall.a.x >= ship->getShipX() - bigRadius) {
		leftWall.c = red;
		if (leftWall.a.x >= ship->getShipX() - smallRadius) {
			ship->resetShipValues();
			return;
		}
	} else {
		leftWall.c = green;
	}
	if (rightWall.a.x <= ship->getShipX() + bigRadius) {
		rightWall.c = red;
		if (rightWall.a.x <= ship->getShipX() + smallRadius) {
			ship->resetShipValues();
			return;
		}
	} else {
		rightWall.c = green;
	}
	if (botWall.a.y >= ship->getShipY() - bigRadius) {
		botWall.c = red;
		if (botWall.a.y >= ship->getShipY() - smallRadius) {
			ship->resetShipValues();
			return;
		}
	} else {
		botWall.c = green;
	}
}


//Line* GameEngine::getArenaWalls() {
//	Line walls [4] = { topWall, leftWall, rightWall, botWall };
//	printf("walls 1 %f\n", walls[0].a.x);
//	printf("walls 2 %f\n", walls[1].a.x);
//	printf("walls 3 %f\n", walls[2].a.x);
//	printf("walls 4 %f\n", walls[3].a.x);
//	return walls;
//}

Line GameEngine::getTopWall() {
	return topWall;
}

Line GameEngine::getBotWall() {
	return botWall;
}

Line GameEngine::getLeftWall() {
	return leftWall;
}

Line GameEngine::getRightWall() {
	return rightWall;
}