#pragma once
#ifndef INTERFACE
#define INTERFACE

#include"myglut.h"
#include "tree.h"
#include <vector>
#include <string>
#include <GL/glut.h>

using namespace std;

void launch_menu(int mode, string& structure);

void draw_string(std::string& str);

void renderScene(void); 

void proccessMouse(int button, int state, int x, int y);


class menu : public tree {
private:
	vector<point> button = vector<point>(2);
	void(menu::* action)(void) = &menu::pass;

	void pass() { return; }  

	void init_buttons(float w, float h); 

	void draw_name(menu* ptr);


public:
	menu() {}
	menu(std::string& S) : tree(S) {
		if (S.find('<') != string::npos) {
			this->action = &menu::start_dialogue;
		}
	}

	bool search_ans(string& ans); 

	void start_dialogue();

	void draw_children(float width, float height);  

	void click(point p);

	void draw_name(menu* ptr);

	bool between(point p, menu* m);
};

class text_tree {
private:
	std::string str;

	menu* create_tree(std::string& s);

	vector<text_tree> get_subemu(std::string& tmp, char del1 = ' ', char del2 = ' ');

	string first_child(string& children); 

	string::iterator find_separator(string& s, char sym);

	string first_brackets(string& s, char del1, char del2);  

public:
	text_tree() {}
	text_tree(string& init) { str = init; }

	menu* create_tree() { return create_tree(str); } 
};

#endif 
