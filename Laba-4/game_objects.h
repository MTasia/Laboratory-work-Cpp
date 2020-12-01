#pragma once
#ifndef GAME_OBJECTS
#define GAME_OBJECTS

#include"geometry.h"

using namespace std;


void init_list(vector<vector<int>>& objects);

enum figure_types {
	POLYGON = 1,
	CIRCLE
};

enum object_type {
	LIMITS = 0,
	RACKET,
	BALL,
	BLOCK,
	BONUS
};


// main class for all objects
class object {
protected:
	figure fig;  // form of the object
	object_type type;  // type for recognizing in action

public:
	virtual void action(object& a) = 0;  // response to collision

	virtual void draw_object() = 0;  // drawing func
};


// moving objects (ball, racket, bonus)
class moving_objects : public object {
public:
	moving_objects() {}

	virtual void collision(object& a) = 0;  // checks whether there is a collision with "a" and triggers its action

	virtual void change_pos(int orientation = 0) = 0;  // changing position with every rendering cycle
};


class bonus : public moving_objects {
private:
	point acceleration;  // bonus speed, center+=acceleration for every rendering cycle

public:
	int bonus_type;  // for racket

	bonus();
	bonus(int key);

	void collision(object& a) override;

	void change_pos(int orientation = 0) override;

	void draw_object() override { fig.draw(); }

	void action(object& a) override;
};


class borders : public object {
public:
	borders(int h, int w, int health);

	void draw_object() override { fig.draw(); }

	void action(object& a) override {};
};


class ball : public moving_objects {
private:
	point acceleration;

public:
	ball(int k_speed, int k_size);

	void reflection();  // reflect off the plane

	void collision(object& a) override;

	void change_pos(int orientation = 0) override;

	void action(object& a) override {};

	void draw_object() override { fig.draw(); }
};


class racket : public moving_objects {
public:
	float acceleration = 6;

public:
	racket(int k_speed, int k_size);

	void collision(object& a) override {};

	void action(object& a) override;

	void draw_object() override { fig.draw(); };

	void change_pos(int orientation = 0) override;
};


class block : public object {
private:
	int lives;

public:
	block(int health, point center, point param);

	void draw_object() override { fig.draw(); }

	void action(object& a) override;
};


class object_list {
private:
	vector<object*> main_objects;
	vector<object*> bonuses;
	vector<object*> blocks;

public:
	object_list(vector<vector<int>>& objects);

	void find_collision(ball* a);
	void find_collision(bonus* a);

	void dead_elem(object* dead_block);

	void generate_bonus();

	void move_racket(int orientation);
	void move_ball();
	void move_bonus();

	void draw();
};

#endif 