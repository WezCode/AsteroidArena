#include "Arena.h"
#include "GameEngine.h"

Arena::Arena() {


	arenaSizeRatio = 0.9;

	float arenaWallX = gameOrthoWidth * arenaSizeRatio;
	float arenaWallY = gameOrthoHeight * arenaSizeRatio;

	topWall = { Point { -arenaWallX, arenaWallY }, Point { arenaWallX, arenaWallY }, green };
	botWall = { Point { -arenaWallX, -arenaWallY }, Point { arenaWallX, -arenaWallY }, green };
	leftWall = { Point { -arenaWallX, -arenaWallY }, Point { -arenaWallX, arenaWallY }, green };
	rightWall = { Point { arenaWallX, -arenaWallY }, Point { arenaWallX, arenaWallY }, green };
}
