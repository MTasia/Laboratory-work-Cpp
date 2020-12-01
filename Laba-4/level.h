#pragma once
#ifndef LEVEL
#define LEVEL

#include "game_objects.h"
#include <vector>
#include <string>
#include <ctype.h>
#include <fstream>

using namespace std;

class level {
private:
	vector<vector<int>>  all_objects;

	void end_game(); // lives = 0

public:
	level(string& file_name);  // init level

	void start_game();  // draw level
};

#endif
