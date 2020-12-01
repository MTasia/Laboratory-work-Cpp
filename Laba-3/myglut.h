#pragma once
#ifndef MYGLUT
#define MYGLUT
#include <string>
#include <GL/glut.h>

typedef void(*key_func)(int, int, int);
typedef void(*mouse_func)(int, int, int, int);
typedef void(*render_func)();

void draw_string(std::string& str);

void init(int mode, mouse_func proccessMouse, render_func renderScene, render_func idl);

void new_window(int argc, char** argv, mouse_func proccessMouse, render_func renderScene);


class point {
private:
	float x;
	float y;

public:
	point() { x = y = 0; }
	point(float x1, float y1) { x = x1; y = y1; }

	void put_point() { glVertex2d(x, y); }

	bool between(point& a, point& b) {
		if (x > a.x && x < b.x && y > a.y && y < b.y)
			return true;
		return false;
	}

	void set_name_pos() {
		glRasterPos2f(x, y);
	}

	point operator + (point& rv) {
		point res(x + rv.x, y + rv.y);
		return point(x + rv.x, y + rv.y);
	}

	point& operator / (int rv) {
		point res(x / rv, y / rv);
		return res;
	}
};

#endif