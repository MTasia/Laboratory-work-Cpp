#include"myglut.h"

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


void init(int mode, mouse_func proccessMouse, render_func renderScene, render_func idl) {
	glutInit(0, NULL);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 600);
	if (mainWindow == -1) {
		mainWindow = glutCreateWindow("Menu");
	}

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	glutIdleFunc(renderScene);

	glutKeyboardFunc(processNormalKeys);
	glutMouseFunc(proccessMouse);
}

int last_window;

void new_window(int argc, char** argv, mouse_func proccessMouse, render_func renderScene) {
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(300, 300);
	last_window = glutCreateWindow("dialog");

	init(argc, argv, proccessMouse, renderScene, renderScene);

}