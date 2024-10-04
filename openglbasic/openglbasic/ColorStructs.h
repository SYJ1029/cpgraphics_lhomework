#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
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