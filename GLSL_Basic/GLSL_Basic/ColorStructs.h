#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#define MAX_INDEX 12
#define MAX_INDEX10 5



typedef struct Mycolor {
	GLclampf red;
	GLclampf green;
	GLclampf blue;
	GLclampf alpha;

}MyCol;

typedef struct MyObjectColor {
	GLfloat R;
	GLfloat G;
	GLfloat B;
}MyObjCol;


typedef struct GLPos {
	GLfloat x;
	GLfloat y;
	GLfloat z;

	/*bool operator=(const GLPos &pos){
		this->x = pos.x;
		this->y = pos.y;
		this->z = pos.z;
	}*/
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
