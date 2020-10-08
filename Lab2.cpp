#include<gl/glut.h>

class Point {
private:
	float x;
	float y;

public:
	Point() { x = 0, y = 0; };
	Point(float x1, float y1) { x = x1, y = y1; };

	float Getx(void) { return x; };
	float Gety(void) { return y; };


	void RevX() { x = -x; };
	void RevY() { y = -y; };

	int CmpY(Point rv) {
		if (y <= rv.y)
			return 1;
		return 0;
	}

	int CmpX(Point rv) {
		if (x <= rv.x)
			return 1;
		return 0;
	}

	void PutPoint() {
		glVertex2d(x, y);
	}

	Point& operator += (Point& rv) {
		x += rv.x;
		y += rv.y;
		return *this;
	}

	Point operator - (Point rv) {
		return(Point(x - rv.x, y - rv.y));
	}

	Point operator * (int rv) {
		return Point(x * rv, y * rv);
	}

	Point operator - () {
		return(Point(-x, -y));
	}

	Point operator + (Point& rv) {
		return(Point(x + rv.x, y + rv.y));
	}
};


class Line {
protected:
	Point p1;
	Point p2;

public:
	Line(Point a, Point b) { p1 = a, p2 = b; };

	Point GetP1() { return p1; };
	Point GetP2() { return p2; };

	void RevX() {
		p1.RevX();
		p2.RevX();
	}

	void RevY() {
		p1.RevY();
		p2.RevY();
	}

	int CheckY(Point& rv) {
		if (p1.CmpY(rv) || p2.CmpY(rv))
			return 1;
		return 0;
	}

	int CheckX(Point& rv) {
		if (p1.CmpX(rv) || p2.CmpX(rv))
			return 1;
		return 0;
	}

	Line& operator += (Line rv) {
		p1 += rv.p1;
		p2 += rv.p2;
		return *this;
	}

	Line& operator = (Line rv) {
		p1 = rv.p1;
		p2 = rv.p2;
		return *this;
	}

	const Line operator - (Line rv) {
		return(Line(p1 - rv.p1, p2 - rv.p2));
	}

	const Line operator - () {
		return(Line(-p1, -p2));
	}

	const Line operator + (Line rv) {
		return(Line(p1 + rv.p1, p2 + rv.p2));
	}
};

Line line = Line(Point(-1, 0), Point(1, 1));
Line speed = Line(Point(0.01, 0.01), Point(0.01, 0.01));

void Borders() {
	glBegin(GL_LINE_STRIP);
	glVertex2d(-3, -3);
	glVertex2d(-3, 3);
	glVertex2d(3, 3);
	glVertex2d(3, -3);
	glVertex2d(-3, -3);
	glEnd();
}

void DrawLine(Line& line) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2d(line.GetP1().Getx(), line.GetP1().Gety());
	glVertex2d(line.GetP2().Getx(), line.GetP2().Gety());
	glEnd();
}

void DrawTrace(Line& line, Line& speed) {
	glColor3f(1.0f / 2, 1.0f / 2, 1.0f / 2);
	glBegin(GL_POLYGON);
	glVertex2d(line.GetP1().Getx(), line.GetP1().Gety());
	glVertex2d(line.GetP2().Getx(), line.GetP2().Gety());
	glVertex2d(line.GetP2().Getx() - 5 * speed.GetP2().Getx(), line.GetP2().Gety() - 5 * speed.GetP2().Gety());
	glVertex2d(line.GetP1().Getx() - 5 * speed.GetP2().Getx(), line.GetP1().Gety() - 5 * speed.GetP1().Gety());
	glEnd();
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	Borders();
	DrawLine(line);
	DrawTrace(line, speed);

	line = speed;

	if (line.GetP1().Getx() <= -3 || line.GetP1().Getx() >= 3 || line.GetP2().Getx() <= -3 || line.GetP2().Getx() >= 3) {
		speed.RevX();
	}
	else if (line.GetP1().Gety() <= -3 || line.GetP1().Gety() >= 3 || line.GetP2().Gety() <= -3 || line.GetP2().Gety() >= 3) {
		speed.RevY();
	}

	glutSwapBuffers();
}

void changeSize(int w, int h) {
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_LEFT:
		speed = Line(Point(-0.01, 0), Point(-0.01, 0));
		break;
	case GLUT_KEY_DOWN:
		speed = Line(Point(0, -0.01), Point(0, -0.01));
		break;
	case GLUT_KEY_RIGHT:
		speed = Line(Point(0.01, 0), Point(0.01, 0));
		break;
	case GLUT_KEY_UP:
		speed = Line(Point(0, 0.01), Point(0, 0.01));
		break;
	}
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Lab_2");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	glutMainLoop();

	return 0;
}