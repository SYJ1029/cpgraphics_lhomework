
#include "ObjStruct.h"
using namespace std;

#define LETDOWN 0
#define LETUP 1
#define MAX_INDEX 5
#define TIME 20

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid MyTimer(int time);
//GLvoid MouseMove(int x, int y);
Pos WintoGL(int x, int y, int w, int h);
bool SetRect(Pos center, float size);
//void glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);


MyCol mycolor = { 0.1f, 0.1f, 0.1f, 1.0f };
MyObjCol objColor[4];
RECTAnimaion rect[MAX_INDEX];
int rectindex = 0;
Pos Screensize = { 800, 800 };
float prevx = 0, prevy = 0;

bool timer_set[4] = { false };
bool first = true;
bool newcol = true;

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
	srand(time(NULL));

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMainLoop(); // 이벤트 처리 시작
}


bool SetRect(Pos center, float size) {

	for (int i = 0; i < MAX_INDEX; i++) {
		if (rect[i].maked == false) {
			rect[i].SetPos(center.x - (size / 2), center.y + (size / 2),
				center.x + (size / 2), center.y - (size / 2));
			rect[i].SetCol((float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX));

			
			return true;
		}
	}

	return false;
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

int ChangeRectPick(Pos newPos) {

	for (int i = MAX_INDEX - 1; i >= 0; i--) {
		if (rect[i].maked)
			if (CheckMounseIn(newPos, i, rect[i].pos)) {

				return i;
			}

	}

	return -1;
}

int ChangeRectSize(int option, int i) {

	float token;
	switch (option) {

	case LETDOWN:
		break;
	case LETUP:
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




GLvoid Mouse(int button, int state, int x, int y) {
	Pos newpos;
	if (state == GLUT_DOWN) {
		newpos = WintoGL(x, y, Screensize.x, Screensize.y);
		switch (button) {
		case GLUT_LEFT_BUTTON:
			SetRect(newpos, 0.1);

			/*if (ChangeRectPick(newpos) != -1) {
				
				break;
			}*/
			/*else {

				break;
			}*/
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
			}
		}
	}

	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y) {
	
}


void Set_NewrectPos(Pos* pos1, Pos* pos2) {

	*pos1 = { (float)((float)rand() / RAND_MAX) * Screensize.x, (float)((float)rand() / RAND_MAX) * Screensize.y };

	float x = (*pos1).x + 50;
	float y = (*pos1).y + 50;

	*pos2 = { x, y };


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

	int timeindex = (int)(key - '0') - 1;

	if (timer_set[timeindex] == false || (timeindex != 0 && timeindex != 1)) {
		first = true;


		for (int i = 0; i < 4; i++) {
			if (i == timeindex)
				timer_set[i] = true;

			else timer_set[i] = false;
		}

		switch (key) {
		case '1':

			for (int i = 0; i < MAX_INDEX; i++) {
				if (rect[i].maked)
					rect[i].zigzag = false;
			}
			//glutTimerFunc(10, MyTimer, 1);
			break;
		case '2':


			for (int i = 0; i < MAX_INDEX; i++) {
				if (rect[i].maked) {
					rect[i].zigzag = true;
					rect[i].Setanimation();
				}

			}
			//glutTimerFunc(10, MyTimer, 2);
			break;
		case '3':
			for (int i = 0; i < MAX_INDEX; i++) {
				if (rect[i].maked && rect[i].upcnt != 0) {
					rect[i].upcnt = 0;
					timer_set[timeindex] = false;
				}
				else if (rect[i].maked) {
					rect[i].SetUpCnt();
				}

			}
			break;
		case '4':
			newcol = !(newcol);
			break;
		case 's':
			for (int i = 0; i < MAX_INDEX; i++) {
				if (i < 4)
					timer_set[i] = false;

				if (rect[i].maked)
					rect[i].zigzag = false;
			}


			break;
		case 'm':
			for (int i = 0; i < MAX_INDEX; i++) {
				if (rect[i].maked) {
					rect[i].RevertPos();
				}

			}
			break;
		case 'r':
			for (int i = 0; i < MAX_INDEX; i++) {
				rect[i].Clear();
			}
			break;
		case 'q':
			glutDestroyWindow(glutGetWindow());
		default:
			break;
		}
	}
	else if (timeindex == 0 || timeindex == 1) {
		for (int i = 0; i < MAX_INDEX; i++) {
			if (i < 4)
				timer_set[i] = false;

			if (rect[i].maked)
				rect[i].zigzag = false;
		}
	}


	if (first && key >= '0' && key <= '9') {
		if(timeindex == 0 || timeindex == 1)
			glutTimerFunc(TIME, MyTimer, timeindex + 1);
		else
			glutTimerFunc(TIME * 10, MyTimer, timeindex + 1);

		first = false;
	}

	glutPostRedisplay();
}

GLvoid MyTimer(int time) {

	if (timer_set[time - 1]) {
		switch (time) {
		case 1:
			for (int i = 0; i < MAX_INDEX; i++) {
				if (rect[i].maked) {
					rect[i].zigzag = false;
					rect[i].Move();

				}
			}
			/*if (timer_set[0])
				glutTimerFunc(10, MyTimer, 1);*/
			glutTimerFunc(TIME, MyTimer, time);
			break;
		case 2:
			for (int i = 0; i < MAX_INDEX; i++) {
				if (rect[i].maked) {
					
					rect[i].Move();

				}
			}
		/*	if (timer_set[1])
				glutTimerFunc(10, MyTimer, 2);*/
			glutTimerFunc(TIME, MyTimer, time);
			break;
		case 3:
			for (int i = 0; i < MAX_INDEX; i++) {
				if (rect[i].maked) {
					rect[i].ChangeSize();
				}
			}
			glutTimerFunc(TIME * 10, MyTimer, time);
			break;
		case 4:

			for (int i = 0; i < MAX_INDEX; i++) {
				if (rect[i].maked && newcol) {
					rect[i].SetCol((float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX));
				}
			}

			glutTimerFunc(TIME * 10, MyTimer, time);
			break;
		}

	}

	glutPostRedisplay();
}