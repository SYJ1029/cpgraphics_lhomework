#include "ColorStructs.h"

using namespace std;

#define NO7_VERTEX 1
#define NO7_LINE 2
#define NO7_TRIANGLE 3
#define NO7_RECT 6


typedef struct GLPos {
	GLfloat x;
	GLfloat y;
	GLfloat z;

}GLPos;

GLPos WintoGL(int x, int y, int w, int h) {
	GLPos newpos;


	newpos.x = ((float)x - (float)(w / 2));
	newpos.x /= ((float)w / 2);
	newpos.y = ((float)y - (float)(h / 2));
	newpos.y /= ((float)h / 2);

	newpos.y = newpos.y * -1;

	newpos.z = 0.0;

	return newpos;
}


class Triangle {

};
