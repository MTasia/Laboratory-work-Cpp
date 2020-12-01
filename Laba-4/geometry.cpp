#include "geometry.h"
#include <ctime>
int random(int a, int b) {
	if (a > 0) return a + rand() % (b - a);
	else return a + rand() % (abs(a) + b);
}

void figure::draw_circle() {
	glColor3f(color[0], color[1], color[2]);
	float r = sqrt(diag.min_x(diag).min_y(center).square());
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < 20; ii++) {
		float theta = 2.0f * 3.1415926f * float(ii) / float(20);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		(point(x, y) + center).put_point();

	}
	glEnd();
}

void figure::draw_polygon() {
	glBegin(GL_POLYGON);
	glColor3f(color[0], color[1], color[2]);
	diag.put_point();
	diag.reflect_y(center).put_point();
	diag.reflect_x(center).reflect_y(center).put_point();
	diag.reflect_x(center).put_point();
	glEnd();
}


figure::figure(point param_center, int figure, point param) {
	center = param_center;
	diag = param;
	if (figure == 2)
		draw_function = &figure::draw_circle;
	for (int i = 0; i < 3; i++)
		color.push_back((float)random(0, 255) / 255);
}

figure::figure(point param_center, int figure, point param, vector<float>paint) {
	center = param_center;
	diag = param;
	if (figure == 2)
		draw_function = &figure::draw_circle;
	color = paint;
}

void figure::move(point speed) {
	point param = diag - center;
	center = center + speed;
	diag = center + param;
}

bool figure::check_collision(figure& obj) {
	if (obj.is_inside(diag) || obj.is_inside(diag.reflect_x(center).reflect_y(center)))
		return true;
	return false;
}

void figure::change_color() {
	color[0] = (float)random(0, 255) / 255;
	color[1] = (float)random(0, 255) / 255;
	color[2] = (float)random(0, 255) / 255;
}

int figure::is_inside(figure& obj) {
	if (diag < obj.diag == 2 ||
		obj.diag.reflect_x(obj.center).reflect_y(obj.center) < diag.reflect_x(center).reflect_y(center) == 2)
		return 2;
	else if (diag < obj.diag == 3)
		return 3;
	else if (obj.diag.reflect_x(obj.center).reflect_y(obj.center) < diag.reflect_x(center).reflect_y(center) == 3)
		return 4;
	else if (diag < obj.diag == 1 ||
		obj.diag.reflect_x(obj.center).reflect_y(obj.center) < diag.reflect_x(center).reflect_y(center) == 1)
		return 1;
	return 0;
}

int figure::is_inside(point p) {
	if (p < diag == 1 && diag.reflect_x(center).reflect_y(center) < p == 1)
		return 1;
	return 0;
