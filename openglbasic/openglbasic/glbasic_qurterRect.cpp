
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

void main(int argc, char** argv) { //--- 윈도우 출력하고 콜백함수 설정 { //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
	glutInitWindowSize(Screensize.x, Screensize.y); // 윈도우의 크기 지정
	glutCreateWindow("Example1"); // 윈도우 생성
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl
			;
		exit(EXIT_FAILURE);
	}
	else
		cout << "GLEW Initialized\n";
	SetRect();

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	glutMainLoop(); // 이벤트 처리 시작
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
	glClearColor(mycolor.red, mycolor.green, mycolor.blue, mycolor.alpha); // 바탕색을 ‘blue’
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다


	for (int i = 0; i < 4; i++) {
		glColor3f(rect[i].col.R, rect[i].col.G, rect[i].col.B);
		cout << i + 1 << "rect: (" << rect[i].col.R << ", " << rect[i].col.G << ", " << rect[i].col.B << ")" << endl << endl;
		glRectf(rect[i].pos[0].x, rect[i].pos[0].y,
			rect[i].pos[1].x, rect[i].pos[1].y);
	}
	cout << endl;

	glutSwapBuffers(); // 화면에 출력하기


}

GLvoid Reshape(int w, int h) { //--- 콜백 함수: 다시 그리기 콜백 함수 {
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