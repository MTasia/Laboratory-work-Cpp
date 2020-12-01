#include"level.h"

using namespace std;


class my_string {
private:
	string str;
public:
	my_string(string& s) { str = s; }

	vector<int> get_params() {
		string tmp;
		vector<int> res;
		for (auto i : str) {
			if (isdigit(i))
				tmp += i;
			else if (i == ',' || i == ')') {
				res.push_back(stoi(tmp));
				tmp = "";
			}
		}
		return res;
	}

	int get_type() {
		string tmp;
		const char* s;
		switch (str[0]) {
		case 'R':
			return 1;
		case 'B':
			if (str[1] == 'a')
				return 2;
			else if (str[1] == 'l')
				return 3;
			else if (str[1] == 'o')
				return 4;
		case 'L':
			return 0;
		default:
			return -1;
		}

	}

	vector<int> get_object() {
		vector<int> res = this->get_params();
		res.push_back(this->get_type());
		return res;
	}
};


level::level(string& file_name) {
	ifstream fin(file_name);
	string a;
	all_objects.clear();
	while (getline(fin, a)) {
		all_objects.push_back(my_string(a).get_object());
	}
	fin.close();
}

void level::start_game() {
	init_list(all_objects);
	glutMainLoop();
}