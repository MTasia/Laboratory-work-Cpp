#include "menu.h"

menu* m;

void launch_menu(int mode, string& structure) {
	m = text_tree(structure).create_tree();
	init(mode, proccessMouse, renderScene, renderScene);
	glutMainLoop();
}

void draw_string(std::string& str) {
	for (auto sym : str) {
		if (sym == '<') 
			return;
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, sym);
	}
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(1.0f);

	glColor3f(10, 30, 99);

	m->draw_children(700, 600);

	glFinish();
	glutSwapBuffers();
}

void proccessMouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			m->click(point((float)x - 350, -((float)y - 300)));
	}
}


menu* text_tree::create_tree(std::string& s) {
	vector<text_tree> submenu_list = this->get_subemu(s, '(', ')');

	menu* t1 = new menu();
	if (submenu_list[0].str.size() == 0) {
		return t1;
	}
	menu* t = new menu(submenu_list[0].str);
	for (int i = 1; i < submenu_list.size(); i++) {
		t->add_child(create_tree(submenu_list[i].str));
	}
	return t;
}

vector<text_tree> text_tree::get_subemu(std::string& tmp, char del1, char del2) {
	vector<text_tree> elems;
	string name = tmp.substr(0, tmp.find_first_of(del1));
	elems.push_back(text_tree(name));
	if (tmp.size() == 0)
		return elems;

	string children = first_brackets(tmp, del1, del2); 

	string child;

	do {
		child = first_child(children);
		elems.push_back(child);
	} while (child != children);

	return elems;
}

string text_tree::first_child(string& children) {
	string::iterator comma_pos = find_separator(children, ',');
	if (comma_pos == children.end()) {
		return children;
	}
	string tmp = children.substr(0, comma_pos - children.begin());
	children.erase(children.begin(), comma_pos + 1);

	return tmp;
}

string::iterator text_tree::find_separator(string& s, char sym) {
	int counter = 0;
	for (auto pos = s.begin(); pos < s.end(); pos++) {
		if (*pos == '(' || *pos == '<')
			counter++;
		else if (*pos == ')' || *pos == '>')
			counter--;
		else if (*pos == ',' && counter == 0)
			return pos;
	}
	return s.end();
}

string text_tree::first_brackets(string& s, char del1, char del2) {
	int open_pos = s.find_first_of(del1);
	int close_pos = s.find_last_of(del2);
	return s.substr(open_pos + 1, close_pos - open_pos - 1);
}


void menu::init_buttons(float w, float h) {
	float step = h / children.size() / 2;
	for (int i = 0; i < children.size(); i++) {
		static_cast<menu*>(this->children[i])->button[0] = point(-w / 8, step * i - h / 4);
		static_cast<menu*>(this->children[i])->button[1] = point(w / 8, step * (i + 1) - h / 4);
	}
}

void menu::draw_name(menu* ptr) {
	point p1 = (static_cast<menu*>(ptr)->button[0] + static_cast<menu*>(ptr)->button[1]);
	p1 = p1 / 2;
	p1.set_name_pos();
	string name = ptr->get_data();
	draw_string(name);
}

bool menu::search_ans(string& s) {
	for (auto i : this->data) {
		if ((*i) == '<') {
			for (auto j = i; j < this->data.end(); j++) {
				if ((*j) == '>') {
					s = string(i + 1, j);
					this->data.replace(i, j + 1, "");
					return true;
				}
			}
		}
	}
	return false;
}

void menu::start_dialogue() {
	string ans;
	while (search_ans(ans)) {
		menu* t = new menu(ans);
		(*this).add_child(t);
	}
	new_window(0, NULL, proccessMouse, renderScene);

}

void menu::draw_children(float width, float height) {
	init_buttons(width, height);
	for (auto i = first_child(); i != NULL; i = next_child()) {
		draw_name(static_cast<menu*>(i));
	}
}

void menu::click(point p) {
	for (auto i = first_child(); i != NULL; i = next_child()) {
		if (p.between(static_cast<menu*>(i)->button[0], static_cast<menu*>(i)->button[1])) {
			*this = *(static_cast<menu*>(i));
			(this->*action)();
			return;
		}
	}
}