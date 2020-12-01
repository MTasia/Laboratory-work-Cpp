#pragma once
#ifndef GEOMETRY
#define GEOMETRY

#include "glut.h"
#include <vector>
#include <string>

using namespace std;

int random(int a, int b);

class point {
private:
	int x;
	int y;

public:
	point() { x = y = 0; }
	point(float x1, float y1) { x = x1; y = y1; }

	void put_point() {
		glVertex2d(x, y);
	}

	float square() { return x * x + y * y; }

	point reflect_x(point mirror) { return point(2 * mirror.x - x, y); }

	point reflect_y(point mirror) { return point(x, 2 * mirror.y - y); }

	point min_x(point rv) { return (point(x - rv.x, y)); }

	point min_y(point rv) { return (point(x, y - rv.y)); }

	int operator == (point& rv) {
		if (x != rv.x && y != rv.y) return 0;
		else if (x == rv.x && y == rv.x) return 3;
		else if (x == rv.x) return 1;
		else if (y == rv.y) return 2;
	}

	int operator < (point rv) {
		if (x < rv.x && y < rv.y) return 1;
		else if (x < rv.x) return 2;
		else if (y < rv.y)return 3;
		else return 0;
	}

	point operator + (point rv) {
		return point(x + rv.x, y + rv.y);
	}

	point operator - (point rv) {
		return point(x - rv.x, y - rv.y);
	}

	point operator / (int rv) {
		return point(x / rv, y / rv);;
	}
};


class figure {
private:
	point center;
	point diag;
	vector<float>color;
	void(figure::* draw_function)(void) = &figure::draw_polygon;

	void draw_circle();
	void draw_polygon();

public:
	figure() { center = point(0, 0); }
	figure(point param_center, int figure, point param);  // figure: 0 - circle, 1 - polygon, param: radius/diagonal
	figure(point param_center, int figure, point param, vector<float>paint);

	void draw() { (this->*draw_function)(); }
	void change_color();

	void move(point speed);

	int is_inside(figure& obj);
	int is_inside(point p);
	bool check_collision(figure& potential);
};
#endif