#include "Ship.h"
#include <stdio.h>
#include <math.h>

Ship::Ship() {


	this->shipWidth = 100;
	this->shipHeight = 100;

	shipX = -850;
	shipY = -420;

	this->rotation = 0;
	this->velocity = 10;

}

// Updates the ship based on velocity
void Ship::moveFoward(float dt) {

	float radianRotation = this->rotation * 3.141592653589793238462643383279502884 / 180;
	//printf("radian rotation %f \n", radianRotation);
	//printf("sin(radianRotation) %f \n", sin(radianRotation));
	//printf("sin(radianRotation) to 2 decimal places %f \n", roundf(sin(radianRotation) * 100) / 100);
	//negative velocity for x translation (not sure why exactly though O.O)
	float newX = this->shipX + roundf(sin(radianRotation) * 100) / 100 * -velocity * dt * 50;
	float newY = this->shipY + roundf(cos(radianRotation) * 100) / 100 * velocity * dt * 50;

	//printf("newX: %f newY: %f \n", newX, newY);

	this->setX(newX);
	this->setY(newY);
}

int Ship::getShipHeight() {
	return this->shipHeight;
}

int Ship::getShipWidth() {
	return this->shipWidth;
}

int Ship::getRotation() {
	return this->rotation;
}

void Ship::setRotation(int newRotation) {
	rotation = newRotation;
}

float Ship::getShipX() {
	return this->shipX;
}

float Ship::getShipY() {
	return this->shipY;
}

void Ship::setX(float x) {
	shipX = x;
}

void Ship::setY(float y) {
	shipY = y;
}

void Ship::resetShipValues() {
	shipX = -850;
	shipY = -420;
	rotation = -60;
}