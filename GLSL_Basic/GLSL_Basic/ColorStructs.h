#include <iostream>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>


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