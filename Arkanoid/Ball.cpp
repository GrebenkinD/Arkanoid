#include "pch.h"
#include "Ball.h"

Ball::Ball(){}
Ball::~Ball() {}

void Ball::move() {
	x += d_x;
	y += d_y;
}