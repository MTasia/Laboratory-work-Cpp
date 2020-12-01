#include"glut.h"

using namespace std;

int mainWindow = -1;
int subWindow;
int windh, windw;

void changeSize(int wid, int ht) {
	glViewport(0, 0, wid, ht);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-wid / 2, wid / 2, -ht / 2, ht / 2);
	glMatrixMode(GL_MODELVIEW);
	windw = wid;
	windh = ht;
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
}


void init(render_func renderScene, key_func idl) {
	int a = 0;
	char** b = NULL;

	//glutInit(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 600);
	mainWindow = glutCreateWindow("Arcanoid");

	// func registration
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	glutIdleFunc(renderScene);

	// occasion proccessing
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(idl);
}