#include "Patition.h"
using namespace std;


// 사각형을 분할시키는 알고리즘
// 1. 트리구조로 제작
// 2. [사각형의 최대 개수][8]인 이차원 배열 구조로 제작

// 트리라면 처음 사각형을 쪼갤 때는 4개로 쪼개야 함
// 단 처음 나눈 사각형을 쪼갤 때는 각 2개씩만 쪼개면 된다.
// 사각형을 나누는 기준이 가로/세로로 쪼개져 있다.
// 이동을 원활히 구현하기 위해선 4등분 해야함
// 즉 트리구조는 알고리즘이 복잡해서 읽기 힘들 확률이 높다

// 이차원 배열이라면 한 사각형의 최대 파티션 만큼의 배열을 만들면 된다
// 한 사각형은 4개의 파티션을 가지고, 그 4개의 파티션은 각각 2개의 파티션을 가지고 있다.
// 아니 트리구조랑 차이가 없잖아



// 트리구조 구현 과정
// 1. 모체인 사각형이 첫번째 부모
// 2. 부모를 둘로 쪼갠다. 1차 파티션 사각형
// 트리에는 '층'이 있다. 각 층 단위별로 쪼개는 단위를 다르게 하자. 
// 우리는 최대 8개의 파티션일 때 기준으로 안쪽은 상하좌우, 바깥쪽은 대각으로 움직이게 할거다
// 위 계획은 4개의 파티션을 세로로 쪼개야 보기 깔끔할 거다
// 1개 -> 2개 -> 4개 -> 8개다. 홀수층은 가로로 쪼개고, 짝수층은 세로로 쪼갠다
// 
// 내가 만들었던 RECT클래스는 좌상단과 우하단 좌표를 가지고 있었다.
// 1개 -> 2개는 세로로 쪼개야 하니 "가운데 좌표"의 x값을 기준으로 쪼개자
// 2개 -> 4개는 가로로 쪼개야 한다. 쪼개진 두 사각형은 같은 "가운데 좌표"의 y값을 알고 있다. 이걸 토대로 4개의 파티션으로 쪼갠다.
// 4개 -> 8개는 다시 세로로 쪼개야 한다. 이 때 각 정사각형은 같은 가운데 좌표를 공유하게 하고 가 가운데 좌표의 x를 기준으로 쪼개자
// 
// 자 이렇게 해서 트리를 8개로 쪼갰는데, 좀 번거롭다고 생각하지 않는가?

/*
* 1. 우리는 구태여 1 -> 2 -> 4 -> 8을 할 필요가 없다.
*	생각해보자. 1과 2는 굳이 필요하다고 생각하는가?
*	내 말은. 하위 파티션으로 분할한다고 해도, 검색이 아니라 어차피 4개나 8개만 쓸 건데 그 부모까지 일일이 다 돌아댕기면서 움직일거냐는 거다
*	그럼 트리는 존나 비효율적이다. 차라리 연결리스트를 쓰고 말지
*	그냥 4개의 파티션을 연결리스트로 만들어 놓고, 트리 생성 규칙에 따라 2개 씩 쪼개고, 쪼갠 파티션을 이어주고, 이어준 파티션을 덮어씌우면 되지 않는가
*	우리는 사각형을 합칠 일이 없다. 즉 상위 파티션을 다루게 될 일이 좆도 없다
* 
* 2. 그리고, 꼭 연결리스트여야만 되냐?
	 많아봐야 80개인데 이건 사실 좆만하지 않긴 하다.
*	
*/


/*
*  이 문제는 4번의 연장선상이라고 보는게 좋다. 다만 타이머 콜백의 호출속도를 조금 더 빠르게 하자
*  4번을 쓰는 이유는 간단하다. 마우스를 따라 움직이는 게 아니라 자기가 주체적인 속도를 가지고 움직이게 설정했기 때문(기울기를 가지고 계심)
*  더군다나 부모 클래스한테서 calvalue라는 크기를 다루는 변수까지 물려받았다. 4번에서는 안 썼을 뿐이지.
*  4번 클래스의 자식 클래스를 하나 만들자
*  자기 자신을 2개의 새로운 사각형으로 쪼개고, 
*  그 사각형을 초기화해서 움직임을 부여해주고,
*  그 둘을 배열에 할당하면서 자가 자신을 지워버리는 클래스를 만들자
*/


/*
* < 나눠진 파티션은 새로운 사각형으로 만든다는 가정 >
* 
* 배열은 최대 10개에, 최대 8개의 파티션이 움직이므로 [10][8]의 2차원 배열을 만들자
* 0번 째에 기본 사각형이 있다.
* 1. 사각형을 클릭하면 자기 자신을 2개로 나눈 뒤, 포인터 형태로 받은 매개변수 클래스에 적용시켜서 최종적으로 총 메인 시퀀스에서 자기 자신을 지워버린다.
* 2. 두개의 추가적인 사각형에 대해서 같은 작업을 반복하자. 이번에는 2 + i에는 아래 쪽 사각형, 본래 인덱스에는 위쪽 사각형으로 덮어씌우자
* 3. 이제 2개의 파티션을 다시 2개씩 더 쪼개자. 4개로 나눠진 파티션은 0 -> 3 인덱스로 각기 할당된다.
* 4. 추가 파티션을 만들 대는 배열 4개를 배열 8개로 바꿔주는 작업을 거쳐야 한다.
* 5. 4 + i 인덱스에 자신의 우측 사각형, 원래 인덱스에 좌측 사각형을 덮어 씌워주게 하자.
* 
* 자, 모든 사각형은 자신을 둘로 쪼개면서, 1 + i, 2 + i, 4 + i 식으로 자신으 파티션이 오는 조각이 나뉘어진다.
* 그러고 보니 앞의 수는 2배씩 뻥튀기 되고 있다. 그럼 클래스에 저장해 놓고, 파티션에는 그 수를 2배로 불려서 저장하게 하면 되지 않을까?
* 
* 
* <새로 만들 자식 클래스에 추가할 것>
* 1. 위쪽으로 움직이거나, 자르는 기준이 바뀔 때 이를 구현할 수단
* 2. 앞의 인덱스 할당식을 n + i로 일반화 했을 때 이 n값을 저장해놓을 정수형 변수
* 
*/


/*
* < 나눠진 파티션도 하나의 클래스로 관리한다는 가정 >
* 이러면 원래대로 [10]의 1차원 배열로도 충분하다.
* 
* 1. 분기가 발생했을 때, 자신의 중심 좌표를 구하고, 중심 좌표를 중심으로 4개로 쪼개버리자.
* 2. 쪼갬으로서 나오는 여러 좌표들을 "클래스 안에" 저장한다.
* 3. 클래스 내부에서 각기 다른 4개의 사각형에 각기 다른 이동을 적용해준다.
* 4. 8개로 분기할 때는 4개의 파티션을 또 4개로 쪼갤거다. 2개로 쪼개는 과정은 없다.
* 5. 2개씩 파티션을 묶어 생각해서, 두 파티션에 같은 움직임을 적용한다. 즉 16개의 파티션이지만 8개인 것처럼 눈속임을 조져라.
* 
* <새로 만들 자식 클래스에 추가할 것>
* 1. 좌표 2개씩 4개를 담아놓은 배열. 그냥 시원하게 2차원 배열하나 만들자
* 2. 중간 좌표를 저장할 변수 혹은 계산해서 적용할 함수.
* 
* 이거 괜찮다 이걸로 하자.
*/

#define LETDOWN 0
#define LETUP 1
#define MAX_INDEX 10
#define TIME 100


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid MyTimer(int time);
//GLvoid MouseMove(int x, int y);
Pos WintoGL(int x, int y, int w, int h);
bool SetRect();
//void glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);


MyCol mycolor = { 1.0f, 1.0f, 1.0f, 1.0f };
MyObjCol objColor[4];
RECTAnimaion rect[MAX_INDEX];
Patition part[MAX_INDEX][8];
int rectindex = 0;
Pos Screensize = { 800, 800 };
float prevx = 0, prevy = 0;

bool timer_set[4] = { false };
bool first = true;
bool newcol = true;

float xdelta = 0, ydelta = 0;
int MoveOption = MOVESTRAIGHT;

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
	SetRect();

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMainLoop(); // 이벤트 처리 시작
}


void Set_NewrectPos(Pos* pos1, Pos* pos2) {

	*pos1 = { (float)((float)rand() / RAND_MAX) * Screensize.x, (float)((float)rand() / RAND_MAX) * Screensize.y };

	float x = (*pos1).x + 70;
	float y = (*pos1).y + 70;

	*pos2 = { x, y };


	(*pos1) = WintoGL((*pos1).x, (*pos1).y, Screensize.x, Screensize.y);
	(*pos2) = WintoGL((*pos2).x, (*pos2).y, Screensize.x, Screensize.y);

}

bool SetRect() {
	rectindex = ((float)((float)rand() / RAND_MAX * 5)) + 5;
	rectindex = ((float)((float)rand() / RAND_MAX * 5)) + 5;


	Pos newPos1 = { 0 }, newPos2 = { 0 };
	for (int i = 0; i < rectindex; i++) {
		if (part[i][0].maked == false) {
			Set_NewrectPos(&newPos1, &newPos2);
			part[i][0].SetPos(newPos1.x, newPos1.y,
				newPos2.x, newPos2.y);
			part[i][0].SetCol((float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX));


		}
	}

	return true;
}

GLvoid drawScene() {
	glClearColor(mycolor.red, mycolor.green, mycolor.blue, mycolor.alpha); // 바탕색을 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다


	for (int i = 0; i < rectindex; i++) {
		for (int j = 0; j < 8; j++) {
			if (part[i][j].maked) {
				glColor3f(part[i][j].col.R, part[i][j].col.G, part[i][j].col.B);
				glRectf(part[i][j].pos[0].x, part[i][j].pos[0].y,
					part[i][j].pos[1].x, part[i][j].pos[1].y);
			}

		}
		/*if (rect[i].maked) {
			glColor3f(rect[i].col.R, rect[i].col.G, rect[i].col.B);
			glRectf(rect[i].pos[0].x, rect[i].pos[0].y,
				rect[i].pos[1].x, rect[i].pos[1].y);
		}*/
	}
	cout << endl;

	glutSwapBuffers(); // 화면에 출력하기


}

GLvoid Reshape(int w, int h) { //--- 콜백 함수: 다시 그리기 콜백 함수 {
	glViewport(0, 0, w, h);
	Screensize.x = w;
	Screensize.y = h;
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

//
//Pos GetFlag(int j) {
//
//}


void GetDelta(int option, int i) {
	Pos result;

	switch (option) {
	case MOVESTRAIGHT:
		if (part[i][0].maked) {
			part[i][0].xflag = -0.04, part[i][0].yflag = 0;
			part[i][1].xflag = 0, part[i][1].yflag = 0.04;
			part[i][2].xflag = 0.04, part[i][2].yflag = 0;
			part[i][3].xflag = 0, part[i][3].yflag = -0.04;
		}
		

		break;
	case MOVEDIAGONAL:
		if (part[i][0].maked) {
			part[i][0].xflag = -0.04, part[i][0].yflag = 0.04;
			part[i][1].xflag = 0.04, part[i][1].yflag = 0.04;
			part[i][2].xflag = 0.04, part[i][2].yflag = -0.04;
			part[i][3].xflag = -0.04, part[i][3].yflag = -0.04;
		}
		
		break;
	case MOVETOGETHER:
		if (part[i][0].maked) {
			for (int j = 0; j < 4; j++) {
				part[i][j].xflag = 0.04, part[i][j].yflag = 0.04;
			}
		}
		
		break;
	case MOVEALL:
		if (part[i][0].maked && part[i][4].maked) {
			/*for (int j = 0; j < 8; j += 4) {
				part[i][j].xflag = 0.04, part[i][j].yflag = 0.04;
			}*/


			part[i][4].xflag = -0.04, part[i][4].yflag = 0;
			part[i][5].xflag = 0.04, part[i][5].yflag = 0.04;
			part[i][6].xflag = 0.04, part[i][6].yflag = -0.04;
			part[i][7].xflag = 0, part[i][7].yflag = -0.04;


			part[i][0].xflag = -0.04, part[i][0].yflag = 0.04;
			part[i][1].xflag = 0, part[i][1].yflag = 0.04;
			part[i][2].xflag = 0.04, part[i][2].yflag = 0;
			part[i][3].xflag = -0.04, part[i][3].yflag = -0.04;
		}
	}

}



GLvoid Mouse(int button, int state, int x, int y) {
	Pos newpos;
	if (state == GLUT_DOWN) {
		newpos = WintoGL(x, y, Screensize.x, Screensize.y);
		switch (button) {
		case GLUT_LEFT_BUTTON:

			//여기에 8파티션 시에 [4]인덱스와[0]에 배열 원소를 쪼개넣는 코드 써넣기

			for (int i = 0; i < MAX_INDEX; i++) {
				if (part[i][0].maked) {
					if (CheckMounseIn(newpos, i, part[i][0].pos)) {
						if (MoveOption == MOVEALL) {
							part[i][0] = part[i][0].SetPatition2(part[i][0], &(part[i][4]));

							part[i][0] = part[i][0].SetPatition((part[i][0]), &(part[i][1]), &(part[i][2]), &(part[i][3]));
							part[i][4] = part[i][4].SetPatition((part[i][4]), &(part[i][5]), &(part[i][6]), &(part[i][7]));
						}
						else
							part[i][0] = part[i][0].SetPatition((part[i][0]), &(part[i][1]), &(part[i][2]), &(part[i][3]));
						GetDelta(MoveOption, i);
						first = true;
						glutTimerFunc(TIME, MyTimer, i);
					}

				}
			}

			
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

GLvoid Keyboard(unsigned char key, int x, int y) {

	Pos pos1 = { -2, -2 };
	Pos pos2 = { -2, -2 };

	int timeindex = (int)(key - '0');


	switch (key) {
	case '1':
		MoveOption = MOVESTRAIGHT;
		first = false;
		break;
	case '2':
		MoveOption = MOVEDIAGONAL;
		first = false;
		break;
	case '3':
		MoveOption = MOVETOGETHER;
		first = false;
		break;
	case '4':
		MoveOption = MOVEALL;
		first = false;
		break;
	default:
		break;
	}

	glutTimerFunc(TIME, MyTimer, timeindex);
	//if (timer_set[timeindex] == false || (timeindex != 0 && timeindex != 1)) {
	//	first = true;


	//	for (int i = 0; i < 4; i++) {
	//		if (i == timeindex)
	//			timer_set[i] = true;

	//		else timer_set[i] = false;
	//	}

	//	switch (key) {
	//	case '1':

	//		for (int i = 0; i < MAX_INDEX; i++) {
	//			if (rect[i].maked)
	//				rect[i].zigzag = false;
	//		}
	//		//glutTimerFunc(10, MyTimer, 1);
	//		break;
	//	case '2':


	//		for (int i = 0; i < MAX_INDEX; i++) {
	//			if (rect[i].maked) {
	//				rect[i].zigzag = true;
	//				rect[i].Setanimation();
	//			}

	//		}
	//		//glutTimerFunc(10, MyTimer, 2);
	//		break;
	//	case '3':
	//		for (int i = 0; i < MAX_INDEX; i++) {
	//			if (rect[i].maked && rect[i].upcnt != 0) {
	//				rect[i].upcnt = 0;
	//				timer_set[timeindex] = false;
	//			}
	//			else if (rect[i].maked) {
	//				rect[i].SetUpCnt();
	//			}

	//		}
	//		break;
	//	case '4':
	//		newcol = !(newcol);
	//		break;
	//	case 's':
	//		for (int i = 0; i < MAX_INDEX; i++) {
	//			if (i < 4)
	//				timer_set[i] = false;

	//			if (rect[i].maked)
	//				rect[i].zigzag = false;
	//		}


	//		break;
	//	case 'm':
	//		for (int i = 0; i < MAX_INDEX; i++) {
	//			if (rect[i].maked) {
	//				rect[i].RevertPos();
	//			}

	//		}
	//		break;
	//	case 'r':
	//		for (int i = 0; i < MAX_INDEX; i++) {
	//			rect[i].Clear();
	//		}
	//		break;
	//	case 'q':
	//		glutDestroyWindow(glutGetWindow());
	//	default:
	//		break;
	//	}
	//}

	/*if (first && key >= '0' && key <= '9') {
		if (timeindex == 0 || timeindex == 1)
			glutTimerFunc(TIME, MyTimer, timeindex + 1);
		else
			glutTimerFunc(TIME * 10, MyTimer, timeindex + 1);

		first = false;
	}*/

	glutPostRedisplay();
}

GLvoid MyTimer(int time) {
	float Xdelta = 0, Ydelta = 0;


	for (int j = 0; j < 4; j++) {
		if (part[time][j].maked && first) {
			part[time][j].Move();
			part[time][j].NewPosDimension(-0.003);
		}
	}
	if (MoveOption == MOVEALL) {
		for (int j = 4; j < 8; j++) {
			if (part[time][j].maked && first) {
				part[time][j].Move();
				part[time][j].NewPosDimension(-0.003);
			}
		}
	}

	if (part[time][0].maked && first) {
		glutTimerFunc(TIME, MyTimer, time);
	}
	//if (timer_set[time - 1]) {
	//	switch (time) {
	//	case 1:
	//		for (int i = 0; i < MAX_INDEX; i++) {
	//			for (int j = 0; j < 4; j++) {
	//				if (part[i][j].maked) {
	//					switch (j) {
	//					case 0:
	//						part[i][j].Move();
	//					}

	//				}
	//			}
	//		}
	//		/*if (timer_set[0])
	//			glutTimerFunc(10, MyTimer, 1);*/
	//		glutTimerFunc(TIME, MyTimer, time);
	//		break;
	//	case 2:
	//		for (int i = 0; i < MAX_INDEX; i++) {
	//			if (rect[i].maked) {

	//				rect[i].Move();

	//			}
	//		}
	//		/*	if (timer_set[1])
	//				glutTimerFunc(10, MyTimer, 2);*/
	//		glutTimerFunc(TIME, MyTimer, time);
	//		break;
	//	case 3:
	//		for (int i = 0; i < MAX_INDEX; i++) {
	//			if (rect[i].maked) {
	//				rect[i].ChangeSize();
	//			}
	//		}
	//		glutTimerFunc(TIME * 10, MyTimer, time);
	//		break;
	//	case 4:

	//		for (int i = 0; i < MAX_INDEX; i++) {
	//			if (rect[i].maked && newcol) {
	//				rect[i].SetCol((float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX));
	//			}
	//		}

	//		glutTimerFunc(TIME * 10, MyTimer, time);
	//		break;
	//	}

	//}

	glutPostRedisplay();
}