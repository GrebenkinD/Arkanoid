#pragma once

class Ball {
public:
	int x, y;
	int d_x, d_y;
	bool activity;
	Ball();
	~Ball();
	void move();
};