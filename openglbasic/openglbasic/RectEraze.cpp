#include "ObjStruct.h"

using namespace std;

#define MAX_INDEX 40
#define COMPARE_MAX 10
#define COMPARE_MIN -10

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
Pos WintoGL(int x, int y, int w, int h);
bool SetRect();


MyCol mycolor = { 1.0f, 1.0f, 1.0f, 1.0f };
MyObjCol objColor[4];
GL_RECT rect[MAX_INDEX];
Erazer erazer;
int rectindex = 0;
int rect_max = 0;
Pos Screensize = { 800, 800 };
float prevx = 0, prevy = 0;

void main(int argc, char** argv) { //--- 윈도우 출력하고 콜백함수 설정 { //--- 윈도우 생성하기
	srand(time(NULL));

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
	glutKeyboardFunc(Keyboard);
	glutMotionFunc(Motion);
	glutMainLoop(); // 이벤트 처리 시작
}



GLvoid drawScene() {
	glClearColor(mycolor.red, mycolor.green, mycolor.blue, mycolor.alpha); // 바탕색을 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다


	for (int i = 0; i < MAX_INDEX; i++) {
		if (rect[i].maked) {
			glColor3f(rect[i].col.R, rect[i].col.G, rect[i].col.B);
			glRectf(rect[i].pos[0].x, rect[i].pos[0].y,
				rect[i].pos[1].x, rect[i].pos[1].y);
		}
	}

	if (erazer.maked) {
		glColor3f(erazer.col.R, erazer.col.G, erazer.col.B);
		glRectf(erazer.pos[0].x, erazer.pos[0].y,
			erazer.pos[1].x, erazer.pos[1].y);
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

void Set_NewrectPos(Pos* pos1, Pos* pos2) {

	*pos1 = { (float)((float)rand() / RAND_MAX) * Screensize.x, (float)((float)rand() / RAND_MAX) * Screensize.y };

	float x = (*pos1).x + 10;
	float y = (*pos1).y + 10;

	*pos2 = { x, y };


	(*pos1) = WintoGL((*pos1).x, (*pos1).y, Screensize.x, Screensize.y);
	(*pos2) = WintoGL((*pos2).x, (*pos2).y, Screensize.x, Screensize.y);


}


bool SetRect() {
	Pos pos1 = { -2, -2 };
	Pos pos2 = { -2, -2 };

	rect_max = rand() / RAND_MAX * 20 + 20;
	
	for (int i = 0; i < rect_max; i++) {
		if (rect[i].maked == false) {
			Set_NewrectPos(&pos1, &pos2);
			rect[i].SetPos(pos1.x, pos1.y, pos2.x, pos2.y);
			rect[i].SetCol((float)((float)rand() / RAND_MAX),
				(float)((float)rand() / RAND_MAX),
				(float)((float)rand() / RAND_MAX));

			rect[i].NewPosDimension(0.0625);

			rect[i].maked = true;
		}
	}


	return true;
}

bool ClearRect() {
	for (int i = 0; i < MAX_INDEX; i++) {
		if (rect[i].maked)
			rect[i].Clear();
	}

	return true;
}


bool SetErazer(Pos mousePos) {

	erazer.SetPos(mousePos);

	return true;
}

int CheckPosInRect(Pos pos, int index) {

	if (pos.x > erazer.pos[0].x && pos.x < erazer.pos[1].x
		&& pos.y > erazer.pos[1].y && pos.y < erazer.pos[0].y) {
		return index;
	}
	/*
	for (int i = 0; i < rect_max; i++) {
		if (pos.x > rect[i].pos[0].x && pos.x < rect[i].pos[1].x
			&& pos.y > rect[i].pos[1].y && pos.y < rect[i].pos[0].y
			&& i != index) {
			return i;
		}
	}*/

	return -1;
}

GLvoid Mouse(int button, int state, int x, int y) {
	Pos newpos;
	bool mouseIn = false;

	if (state == GLUT_DOWN) {
		newpos = WintoGL(x, y, Screensize.x, Screensize.y);
		switch (button) {
		case GLUT_LEFT_BUTTON:
			if (SetErazer(newpos)) {
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
			erazer.Clear();

		}
	}

	glutPostRedisplay();
}

GLvoid Motion(int x, int y) {
	Pos newpos;
	Pos postoken;



	newpos = WintoGL(x, y, Screensize.x, Screensize.y);

	cout << "newpos << (" << newpos.x << ", " << newpos.y << ")" << endl;
	cout << "prevpos << (" << prevx << ", " << prevy << ")" << endl;


	postoken.x = newpos.x - prevx;
	postoken.y = newpos.y - prevy;

	int rect_index = -1;

	if (erazer.maked) {
		erazer.Move(postoken.x, postoken.y);

		//postoken을 재활용 -> 우상단, 좌하단 좌표로 각각 만들어서 충돌 체크

		prevx = newpos.x;
		prevy = newpos.y;
		

		//postoken = { erazer.pos[0].x, erazer.pos[1].y }; //좌하단
		for (int i = rect_max - 1; i >= 0; i--) {
			if (rect[i].maked) {
				for (int j = 0; j < 2; j++) {
					rect_index = CheckPosInRect(rect[i].pos[j], i);
					if (rect_index >= 0) {
						rect[rect_index] = erazer.DeleteRect(rect[rect_index]);
					}

					rect_index = CheckPosInRect({ rect[i].pos[j].x, rect[i].pos[1 - j].y}, i);
					if (rect_index >= 0) {
						rect[rect_index] = erazer.DeleteRect(rect[rect_index]);
					}
				}

				/*postoken = { erazer.pos[0].x, erazer.pos[1].y };
				rect_index = CheckPosInRect({ erazer.pos[0].x, erazer.pos[1].y }, i);
				if (rect_index >= 0) {
					erazer.DeleteRect(rect[rect_index]);
				}*/


			}

		}
	}

	/*for (int i = MAX_INDEX - 1; i >= 0; i--) {*/
	//	if (rect[i].maked && rect[i].chosen) {
	//		rect[i].Move(postoken.x, postoken.y);
	//		/*cout << "rect" << i << ": (" << rect[i].pos[0].x << ", " << rect[i].pos[0].y << ")" << endl;
	//		cout << "(" << rect[i].pos[1].x << ", " << rect[i].pos[1].y << ")" << endl;*/

	//		


	//		break;
	//	}
	//}

	glutPostRedisplay();
}


GLvoid Keyboard(unsigned char key, int x, int y) {

	Pos pos1 = { -2, -2 };
	Pos pos2 = { -2, -2 };
	switch (key) {
	case 'r':
		ClearRect();
		SetRect();
		break;
	default:
		break;
	}


	glutPostRedisplay();
}