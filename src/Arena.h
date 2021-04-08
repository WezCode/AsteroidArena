#pragma once
#include "GameEngine.h"

class Arena {

	public:

		Arena();

	private:

		float arenaSizeRatio;

		Line topWall;
		Line botWall;
		Line leftWall;
		Line rightWall;


};