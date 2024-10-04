
#include "ObjStruct.h"
using namespace std;

#define LETDOWN 0
#define LETUP 1

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
Pos WintoGL(int x, int y, int w, int h);
bool SetRect();
//void glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);


MyCol mycolor = { 0.0f, 0.0f, 0.0f, 1.0f };
MyObjCol objColor[4];
GL_RECT rect[4];
Pos Screensize = { 800, 800 };

void main(int argc, char** argv) { //--- ������ ����ϰ� �ݹ��Լ� ���� { //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(0, 0); // �������� ��ġ ����
	glutInitWindowSize(Screensize.x, Screensize.y); // �������� ũ�� ����
	glutCreateWindow("Example1"); // ������ ����
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl
			;
		exit(EXIT_FAILURE);
	}
	else
		cout << "GLEW Initialized\n";
	SetRect();

	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutMouseFunc(Mouse);
	glutMainLoop(); // �̺�Ʈ ó�� ����
}


bool SetRect() {
	srand(time(NULL));
	rect[0].SetPos(-1.0, 1.0, 0.0, 0.0);
	rect[0].SetCol((float)((float)rand() / RAND_MAX),
		(float)((float)rand() / RAND_MAX),
		(float)((float)rand() / RAND_MAX));

	rect[1].SetPos(0.0, 1.0, 1.0, 0.0);
	rect[1].SetCol((float)((float)rand() / RAND_MAX),
		(float)((float)rand() / RAND_MAX),
		(float)((float)rand() / RAND_MAX));

	rect[2].SetPos(-1.0, 0.0, 0.0, -1.0);
	rect[2].SetCol((float)((float)rand() / RAND_MAX),
		(float)((float)rand() / RAND_MAX),
		(float)((float)rand() / RAND_MAX));

	rect[3].SetPos(0.0, 0.0, 1.0, -1.0);
	rect[3].SetCol((float)((float)rand() / RAND_MAX),
		(float)((float)rand() / RAND_MAX),
		(float)((float)rand() / RAND_MAX));


	return true;
}

GLvoid drawScene() {
	glClearColor(mycolor.red, mycolor.green, mycolor.blue, mycolor.alpha); // �������� ��blue��
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�


	for (int i = 0; i < 4; i++) {
		glColor3f(rect[i].col.R, rect[i].col.G, rect[i].col.B);
		cout << i + 1 << "rect: (" << rect[i].col.R << ", " << rect[i].col.G << ", " << rect[i].col.B << ")" << endl << endl;
		glRectf(rect[i].pos[0].x, rect[i].pos[0].y,
			rect[i].pos[1].x, rect[i].pos[1].y);
	}
	cout << endl;

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�


}

GLvoid Reshape(int w, int h) { //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� {
	glViewport(0, 0, w, h);
}


Pos WintoGL(int x, int y, int w, int h) {
	Pos newpos;
	

	newpos.x = ((float)x - (float)(w / 2));
	newpos.x /= ((float)w / 2);
	newpos.y = ((float)y - (float)(h / 2));
	newpos.y /= ((float)h / 2);

	newpos.y = newpos.y * -1;

	return newpos;
}

bool CheckMounseIn(Pos mousePos, int i, Pos pos[2]) {

	if (mousePos.x >= pos[0].x
			&& mousePos.x <= pos[1].x
			&& mousePos.y <= pos[0].y
			&& mousePos.y >= pos[1].y) 
		return true;

	

	return false;
}

bool ChangeWindowCol() {
	mycolor = { (float)((float)rand() / RAND_MAX), 	(float)((float)rand() / RAND_MAX), 	(float)((float)rand() / RAND_MAX), 1.0f };

	return true;
}

int ChangeRectCol(Pos newPos) {

	for (int i = 0; i < 4; i++) {
		if (CheckMounseIn(newPos, i, rect[i].pos)) {
			rect[i].SetCol((float)((float)rand() / RAND_MAX),
				(float)((float)rand() / RAND_MAX),
				(float)((float)rand() / RAND_MAX));
			return i;
		}
	}

	return -1;
}

int ChangeRectSize(int option, int i) {

	float token;
	switch (option) {

	case LETDOWN:
		rect[i].NewPosDimension(-0.05);
		break;
	case LETUP:
		rect[i].NewPosDimension(0.05);
		break;
	}




	return 1;
}

int SelectRect(Pos newpos) {
	Pos token[2];
	float value;
	for (int i = 0; i < 4; i++) {
		value = rect[i].calvalue;

		rect[i].NewPosDimension(value * -1);

		if (CheckMounseIn(newpos, i, rect[i].pos)) {
			ChangeRectSize(LETUP, i);
		}

		rect[i].NewPosDimension(value);
	}

	return 1;
}



GLvoid Mouse(int button, int state, int x, int y) {
	Pos newpos;
	bool mouseIn = false;

	if (state == GLUT_DOWN) {
		newpos = WintoGL(x, y, Screensize.x, Screensize.y);
		switch (button) {
		case GLUT_LEFT_BUTTON:
			if (ChangeRectCol(newpos) != -1)
				break;
			else {
				ChangeWindowCol();
				break;
			}
		case GLUT_RIGHT_BUTTON:
			for (int i = 0; i < 4; i++) {
				mouseIn = CheckMounseIn(newpos, i, rect[i].pos);
				if (mouseIn) {
					if (ChangeRectSize(LETDOWN, i) != -1) {
						break;
					}
				}
				else {
					if(i == 3)
						SelectRect(newpos);
				}

			}

			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		default:
			break;
		}

	}

	glutPostRedisplay();
}