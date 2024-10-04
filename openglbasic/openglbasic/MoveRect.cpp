
#include "ObjStruct.h"
using namespace std;

#define LETDOWN 0
#define LETUP 1
#define MAX_INDEX 10
#define COMPARE_MAX 10
#define COMPARE_MIN -10

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid MouseMove(int x, int y);
Pos WintoGL(int x, int y, int w, int h);
bool SetRect();
//void glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);


MyCol mycolor = { 1.0f, 1.0f, 1.0f, 1.0f };
MyObjCol objColor[4];
GL_RECT rect[MAX_INDEX];
int rectindex = 0;
Pos Screensize = { 800, 800 };
float prevx = 0, prevy = 0;

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
	srand(time(NULL));

	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	glutKeyboardFunc(Keyboard);
	glutMainLoop(); // �̺�Ʈ ó�� ����
}


bool SetRect() {
	srand(time(NULL));


	return true;
}

GLvoid drawScene() {
	glClearColor(mycolor.red, mycolor.green, mycolor.blue, mycolor.alpha); // �������� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�


	for (int i = 0; i < MAX_INDEX; i++) {
		if (rect[i].maked) {
			glColor3f(rect[i].col.R, rect[i].col.G, rect[i].col.B);
			glRectf(rect[i].pos[0].x, rect[i].pos[0].y,
				rect[i].pos[1].x, rect[i].pos[1].y);
		}
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

int ChangeRectPick(Pos newPos) {

	for (int i = MAX_INDEX - 1; i >= 0; i--) {
		if(rect[i].maked)
			if (CheckMounseIn(newPos, i, rect[i].pos)) {
				rect[i].chosen = true;
				return i;
			}

	}

	return 1;
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


float ComparePos(int option, float a, float b) {
	float result = 0;

	switch (option) {
	case COMPARE_MAX:
		if (a > b)
			return a;
		else 
			return b;
		break;
	case COMPARE_MIN:
		if (a < b)
			return a;
		else
			return b;
		break;
	default:
		break;
	}


	return result;
}


GL_RECT GetnewRect(GL_RECT rect1, GL_RECT rect2) {
	GL_RECT result;

	result.SetPos(
		ComparePos(COMPARE_MIN, rect1.pos[0].x, rect2.pos[0].x),
		ComparePos(COMPARE_MAX, rect1.pos[0].y, rect2.pos[0].y),
		ComparePos(COMPARE_MAX, rect1.pos[1].x, rect2.pos[1].x),
		ComparePos(COMPARE_MIN, rect1.pos[1].y, rect2.pos[1].y)
	);

	result.SetCol((float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX));


	return result;
}


int CheckPosInRect(Pos pos, int index) {
	for (int i = 0; i < MAX_INDEX; i++) {
		if (pos.x > rect[i].pos[0].x && pos.x < rect[i].pos[1].x
			&& pos.y > rect[i].pos[1].y && pos.y < rect[i].pos[0].y
			&& i != index) {
			return i;
		}
	}

	return -1;
}

void MergeRect(int i) {
	Pos pos[4]; // �簢���� 4���� ���� ������.

	
	pos[0] = { rect[i].pos[0].x, rect[i].pos[0].y }; //�»��
	pos[1] = { rect[i].pos[1].x, rect[i].pos[1].y }; //����
	pos[3] = { rect[i].pos[0].x, rect[i].pos[1].y }; //���ϴ�
	pos[2] = { rect[i].pos[1].x, rect[i].pos[0].y }; //���ϴ�


	int anotherRectIndex = 0;
	for (int j = 0; j < 4; j++) {
		anotherRectIndex = CheckPosInRect(pos[j], i);
		if (anotherRectIndex >= 0) {
			rect[i] = GetnewRect(rect[i], rect[anotherRectIndex]);
			rect[anotherRectIndex].Clear();
		}

	}

}

GLvoid Mouse(int button, int state, int x, int y) {
	Pos newpos;
	bool mouseIn = false;

	if (state == GLUT_DOWN) {
		newpos = WintoGL(x, y, Screensize.x, Screensize.y);
		switch (button) {
		case GLUT_LEFT_BUTTON:
			if (ChangeRectPick(newpos) != -1) {
				prevx = newpos.x, prevy = newpos.y;

				break;
			}
			else {

				break;
			}
		case GLUT_RIGHT_BUTTON:
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		default:
			break;
		}

	}
	else {
		for (int i = 0; i < MAX_INDEX; i++) {
			if (rect[i].chosen) {
				MergeRect(i);
				rect[i].chosen = false;
			}
		}
	}

	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y) {
	Pos newpos;
	Pos postoken;
	

	
	newpos = WintoGL(x, y, Screensize.x, Screensize.y);

	cout << "newpos << (" << newpos.x << ", " << newpos.y << ")" << endl;
	cout << "prevpos << (" << prevx << ", " << prevy << ")" << endl;


	postoken.x = newpos.x - prevx;
	postoken.y = newpos.y - prevy;

	for (int i = MAX_INDEX - 1; i >= 0; i--) {
		if (rect[i].maked && rect[i].chosen) {
			rect[i].Move(postoken.x, postoken.y);
			/*cout << "rect" << i << ": (" << rect[i].pos[0].x << ", " << rect[i].pos[0].y << ")" << endl;
			cout << "(" << rect[i].pos[1].x << ", " << rect[i].pos[1].y << ")" << endl;*/

			prevx = newpos.x;
			prevy = newpos.y;
			break;
		}
	}

	glutPostRedisplay();
}


void Set_NewrectPos(Pos* pos1, Pos* pos2) {

	*pos1 = { (float)((float)rand() / RAND_MAX) * Screensize.x, (float)((float)rand() / RAND_MAX) * Screensize.y};

	float x = (*pos1).x + 50;
	float y = (*pos1).y + 50;

	*pos2 = { x, y};


	(*pos1) = WintoGL((*pos1).x, (*pos1).y, Screensize.x, Screensize.y);
	(*pos2) = WintoGL((*pos2).x, (*pos2).y, Screensize.x, Screensize.y);

	/**pos2 = { (float)((float)rand() / RAND_MAX) * 2 - 1, (float)((float)rand() / RAND_MAX) * 2 - 1 };

	while ((*pos1).x == (*pos2).x) {
		(*pos2).x = (float)((float)rand() / RAND_MAX) * 2 - 1;
	}

	while ((*pos1).y == (*pos2).y) {
		(*pos2).y = (float)((float)rand() / RAND_MAX) * 2 - 1;
	}

	float token = 0;
	if ((*pos1).x > (*pos2).x) {
		token = (*pos2).x;
		(*pos2).x = (*pos1).x;
		(*pos1).x = token;
	}

	if ((*pos1).y < (*pos2).y) {
		token = (*pos2).y;
		(*pos2).y = (*pos1).y;
		(*pos1).y = token;
	}*/
}

GLvoid Keyboard(unsigned char key, int x, int y) {

	Pos pos1 = { -2, -2 };
	Pos pos2 = { -2, -2 };
	switch (key) {
	case 'a':
		for (int i = 0; i < MAX_INDEX; i++) {
			if (rect[i].maked == false){
				Set_NewrectPos(&pos1, &pos2);
				rect[i].SetPos(pos1.x, pos1.y, pos2.x, pos2.y);
				rect[i].SetCol((float)((float)rand() / RAND_MAX),
					(float)((float)rand() / RAND_MAX),
					(float)((float)rand() / RAND_MAX));
				rect[i].maked = true;
				break;
			}
		}
		
		break;
	default:
		break;
	}


	glutPostRedisplay();
}