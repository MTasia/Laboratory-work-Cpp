#pragma once
#ifndef MYGLUT
#define MYGLUT
#include <string>
#include <GL/glut.h>

typedef void(*key_func)(int, int, int);
typedef void(*render_func)();

void init(render_func renderScene, key_func idl);


#endif 