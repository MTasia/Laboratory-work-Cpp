#include "game_objects.h"

using namespace std;


object_list* main_list;
int W;
int H;
int lives = 1;
int bonus_probability = 50;

void init_list(vector<vector<int>>& objects) {
	main_list = new object_list(objects);
}


void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(1.0f);

	main_list->move_ball();
	main_list->move_bonus();
	main_list->draw();

	glFinish();
	glutSwapBuffers();
}

void object_list::draw() {
	for (auto i : main_objects) {
		i->draw_object();
	}
	for (auto i : blocks) {
		i->draw_object();
	}
	for (auto i : bonuses)
		i->draw_object();
}

void keys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		main_list->move_racket(-1);
		break;
	case GLUT_KEY_RIGHT:
		main_list->move_racket(1);
		break;
	}
}


void block::action(object& obj) {
	block::lives--;
	if (block::lives == 0) {
		main_list->dead_elem(this);
		main_list->generate_bonus();
	}
	fig.change_color();
}

void racket::action(object& obj) {
	if (static_cast<racket&>(obj).type == BALL)
		return;
	else {
		switch (static_cast<bonus&>(obj).bonus_type) {
		case 0:
			acceleration += 1;
			break;
		case 1:
			lives++;
			break;
		}
	}
}

void bonus::action(object& obj) {
	return;
}


void ball::collision(object& potential) {
	if (fig.check_collision(static_cast<ball&>(potential).fig)) {
		potential.action(*this);
		acceleration = acceleration.reflect_y(point(0, 0));
		fig.move(acceleration);
	}
}

void bonus::collision(object& potential) {
	if (fig.check_collision(static_cast<bonus&>(potential).fig)) {
		potential.action(*this);
		main_list->dead_elem(this);
	}
}

void racket::change_pos(int orientation) {
	fig.move(point(acceleration * orientation, 0));
	if (figure(point(0, 0), POLYGON, point(300, 250)).is_inside(fig) == 2)
		fig.move(point(-acceleration * orientation, 0));
}

void ball::change_pos(int orientation) {
	fig.move(acceleration);
	if (figure(point(0, 0), POLYGON, point(300, 250)).is_inside(fig) == 2)
		acceleration = acceleration.reflect_x(point(0, 0));
	else if (figure(point(0, 0), POLYGON, point(300, 250)).is_inside(fig) == 3)
		acceleration = acceleration.reflect_y(point(0, 0));
	else if (figure(point(0, 0), POLYGON, point(300, 250)).is_inside(fig) == 4) {
		if (--lives == 0)
			exit(0);
		acceleration = acceleration.reflect_y(point(0, 0));
	}
}

void bonus::change_pos(int orientation) {
	fig.move(acceleration);
}


void object_list::dead_elem(object* dead) {
	for (auto i = blocks.begin(); i < blocks.end(); i++) {
		if (*i == dead) {
			blocks.erase(i);
			return;
		}
	}
	for (auto i = bonuses.begin(); i < bonuses.end(); i++) {
		if (*i == dead) {
			bonuses.erase(i);
			return;
		}
	}
}

void object_list::find_collision(ball* obj) {
	for (auto i : blocks) {
		obj->collision(*i);
	}
	obj->collision(*(main_objects[RACKET]));
}

void object_list::find_collision(bonus* obj) {
	obj->collision(*(main_objects[RACKET]));
}


void object_list::move_racket(int orientation) {
	static_cast<racket*>(main_objects[RACKET])->change_pos(orientation);
}

void object_list::move_ball() {
	static_cast<ball*>(main_objects[BALL])->change_pos(1);
	find_collision(static_cast<ball*>(main_objects[BALL]));
}

void object_list::move_bonus() {
	for (auto i : bonuses) {
		static_cast<bonus*>(i)->change_pos();
		find_collision(static_cast<bonus*>(i));
	}
}

vector<object*> generate_blocks(vector<int>& blocks) {
	vector<object*> res;
	float h = W / (10);
	float cent_y = H / 2 - 5;
	int counter = 1;
	float cent_x = -W / 2 + h;

	for (auto i : blocks) {
		for (int j = 0; j < i; j++) {
			res.push_back(new block(counter, point(cent_x, cent_y), point(cent_x, cent_y) + point(h, 5)));
			cent_x += h;
			if (cent_x + h > W / 2) {
				cent_y -= 20;
				cent_x = -W / 2 + h;
			}
		}
		counter++;
	}
	return res;
}

void object_list::generate_bonus() {
	int r = random(0, 100);
	if (r < bonus_probability) {
		bonuses.push_back(new bonus(r % 3));
	}
}

object_list::object_list(vector<vector<int>>& objects) {
	object* a;
	for (auto i : objects) {
		switch (i.back()) {
		case RACKET:
			main_objects.push_back(new racket(i[0], i[1]));
			break;
		case BALL:
			main_objects.push_back(new ball(i[0], i[1]));
			break;
		case BLOCK:
			blocks = generate_blocks(i);
			break;
		case BONUS:
			bonus_probability = i[0];
			break;
		case LIMITS:
			main_objects.push_back(new borders(i[0], i[1], i[2]));

			break;
		}
	}
	init(render, keys);
}


bonus::bonus(int key) {
	fig = figure(point(0, 150), CIRCLE, point(10, 160));
	acceleration = point(0, -5);
	bonus_type = key;
}

block::block(int health, point center, point param) {
	lives = health;
	fig = figure(center, POLYGON, param);
}

racket::racket(int k_speed, int k_size) {
	acceleration *= k_speed;
	vector<float> color{ float(250), float(250), float(250) };
	fig = figure(point(0, -200), POLYGON, point(40 * (1. / k_size), -200 + 5), color);
}

borders::borders(int h, int w, int health) {
	vector<float> color{ 0, float(250), 0 };
	fig = figure(point(0, 0), POLYGON, point(w / 2, h / 2), color);
	W = w;
	H = h;
	lives = health;
}

ball::ball(int k_speed, int k_size) {
	acceleration = point(k_speed, k_speed);
	vector<float> color{ float(250), 0, 0 };
	fig = figure(point(30, -150), CIRCLE, point(40, -150 + 10), color);
	type = BALL;
}