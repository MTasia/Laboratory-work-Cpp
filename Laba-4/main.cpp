#include "level.h"


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	string s("level.txt");
	level(s).start_game();

	return 0;
}
