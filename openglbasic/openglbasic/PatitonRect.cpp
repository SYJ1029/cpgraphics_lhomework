#include "Patition.h"
using namespace std;


// �簢���� ���ҽ�Ű�� �˰���
// 1. Ʈ�������� ����
// 2. [�簢���� �ִ� ����][8]�� ������ �迭 ������ ����

// Ʈ����� ó�� �簢���� �ɰ� ���� 4���� �ɰ��� ��
// �� ó�� ���� �簢���� �ɰ� ���� �� 2������ �ɰ��� �ȴ�.
// �簢���� ������ ������ ����/���η� �ɰ��� �ִ�.
// �̵��� ��Ȱ�� �����ϱ� ���ؼ� 4��� �ؾ���
// �� Ʈ�������� �˰����� �����ؼ� �б� ���� Ȯ���� ����

// ������ �迭�̶�� �� �簢���� �ִ� ��Ƽ�� ��ŭ�� �迭�� ����� �ȴ�
// �� �簢���� 4���� ��Ƽ���� ������, �� 4���� ��Ƽ���� ���� 2���� ��Ƽ���� ������ �ִ�.
// �ƴ� Ʈ�������� ���̰� ���ݾ�



// Ʈ������ ���� ����
// 1. ��ü�� �簢���� ù��° �θ�
// 2. �θ� �ѷ� �ɰ���. 1�� ��Ƽ�� �簢��
// Ʈ������ '��'�� �ִ�. �� �� �������� �ɰ��� ������ �ٸ��� ����. 
// �츮�� �ִ� 8���� ��Ƽ���� �� �������� ������ �����¿�, �ٱ����� �밢���� �����̰� �ҰŴ�
// �� ��ȹ�� 4���� ��Ƽ���� ���η� �ɰ��� ���� ����� �Ŵ�
// 1�� -> 2�� -> 4�� -> 8����. Ȧ������ ���η� �ɰ���, ¦������ ���η� �ɰ���
// 
// ���� ������� RECTŬ������ �»�ܰ� ���ϴ� ��ǥ�� ������ �־���.
// 1�� -> 2���� ���η� �ɰ��� �ϴ� "��� ��ǥ"�� x���� �������� �ɰ���
// 2�� -> 4���� ���η� �ɰ��� �Ѵ�. �ɰ��� �� �簢���� ���� "��� ��ǥ"�� y���� �˰� �ִ�. �̰� ���� 4���� ��Ƽ������ �ɰ���.
// 4�� -> 8���� �ٽ� ���η� �ɰ��� �Ѵ�. �� �� �� ���簢���� ���� ��� ��ǥ�� �����ϰ� �ϰ� �� ��� ��ǥ�� x�� �������� �ɰ���
// 
// �� �̷��� �ؼ� Ʈ���� 8���� �ɰ��µ�, �� ���ŷӴٰ� �������� �ʴ°�?

/*
* 1. �츮�� ���¿� 1 -> 2 -> 4 -> 8�� �� �ʿ䰡 ����.
*	�����غ���. 1�� 2�� ���� �ʿ��ϴٰ� �����ϴ°�?
*	�� ����. ���� ��Ƽ������ �����Ѵٰ� �ص�, �˻��� �ƴ϶� ������ 4���� 8���� �� �ǵ� �� �θ���� ������ �� ���ƴ��鼭 �����ϰųĴ� �Ŵ�
*	�׷� Ʈ���� ���� ��ȿ�����̴�. ���� ���Ḯ��Ʈ�� ���� ����
*	�׳� 4���� ��Ƽ���� ���Ḯ��Ʈ�� ����� ����, Ʈ�� ���� ��Ģ�� ���� 2�� �� �ɰ���, �ɰ� ��Ƽ���� �̾��ְ�, �̾��� ��Ƽ���� ������ ���� �ʴ°�
*	�츮�� �簢���� ��ĥ ���� ����. �� ���� ��Ƽ���� �ٷ�� �� ���� ���� ����
* 
* 2. �׸���, �� ���Ḯ��Ʈ���߸� �ǳ�?
	 ���ƺ��� 80���ε� �̰� ��� �������� �ʱ� �ϴ�.
*	
*/


/*
*  �� ������ 4���� ���弱���̶�� ���°� ����. �ٸ� Ÿ�̸� �ݹ��� ȣ��ӵ��� ���� �� ������ ����
*  4���� ���� ������ �����ϴ�. ���콺�� ���� �����̴� �� �ƴ϶� �ڱⰡ ��ü���� �ӵ��� ������ �����̰� �����߱� ����(���⸦ ������ ���)
*  �����ٳ� �θ� Ŭ�������׼� calvalue��� ũ�⸦ �ٷ�� �������� �����޾Ҵ�. 4�������� �� ���� ������.
*  4�� Ŭ������ �ڽ� Ŭ������ �ϳ� ������
*  �ڱ� �ڽ��� 2���� ���ο� �簢������ �ɰ���, 
*  �� �簢���� �ʱ�ȭ�ؼ� �������� �ο����ְ�,
*  �� ���� �迭�� �Ҵ��ϸ鼭 �ڰ� �ڽ��� ���������� Ŭ������ ������
*/


/*
* < ������ ��Ƽ���� ���ο� �簢������ ����ٴ� ���� >
* 
* �迭�� �ִ� 10����, �ִ� 8���� ��Ƽ���� �����̹Ƿ� [10][8]�� 2���� �迭�� ������
* 0�� °�� �⺻ �簢���� �ִ�.
* 1. �簢���� Ŭ���ϸ� �ڱ� �ڽ��� 2���� ���� ��, ������ ���·� ���� �Ű����� Ŭ������ ������Ѽ� ���������� �� ���� ���������� �ڱ� �ڽ��� ����������.
* 2. �ΰ��� �߰����� �簢���� ���ؼ� ���� �۾��� �ݺ�����. �̹����� 2 + i���� �Ʒ� �� �簢��, ���� �ε������� ���� �簢������ �������
* 3. ���� 2���� ��Ƽ���� �ٽ� 2���� �� �ɰ���. 4���� ������ ��Ƽ���� 0 -> 3 �ε����� ���� �Ҵ�ȴ�.
* 4. �߰� ��Ƽ���� ���� ��� �迭 4���� �迭 8���� �ٲ��ִ� �۾��� ���ľ� �Ѵ�.
* 5. 4 + i �ε����� �ڽ��� ���� �簢��, ���� �ε����� ���� �簢���� ���� �����ְ� ����.
* 
* ��, ��� �簢���� �ڽ��� �ѷ� �ɰ��鼭, 1 + i, 2 + i, 4 + i ������ �ڽ��� ��Ƽ���� ���� ������ ����������.
* �׷��� ���� ���� ���� 2�辿 ��Ƣ�� �ǰ� �ִ�. �׷� Ŭ������ ������ ����, ��Ƽ�ǿ��� �� ���� 2��� �ҷ��� �����ϰ� �ϸ� ���� ������?
* 
* 
* <���� ���� �ڽ� Ŭ������ �߰��� ��>
* 1. �������� �����̰ų�, �ڸ��� ������ �ٲ� �� �̸� ������ ����
* 2. ���� �ε��� �Ҵ���� n + i�� �Ϲ�ȭ ���� �� �� n���� �����س��� ������ ����
* 
*/


/*
* < ������ ��Ƽ�ǵ� �ϳ��� Ŭ������ �����Ѵٴ� ���� >
* �̷��� ������� [10]�� 1���� �迭�ε� ����ϴ�.
* 
* 1. �бⰡ �߻����� ��, �ڽ��� �߽� ��ǥ�� ���ϰ�, �߽� ��ǥ�� �߽����� 4���� �ɰ�������.
* 2. �ɰ����μ� ������ ���� ��ǥ���� "Ŭ���� �ȿ�" �����Ѵ�.
* 3. Ŭ���� ���ο��� ���� �ٸ� 4���� �簢���� ���� �ٸ� �̵��� �������ش�.
* 4. 8���� �б��� ���� 4���� ��Ƽ���� �� 4���� �ɰ��Ŵ�. 2���� �ɰ��� ������ ����.
* 5. 2���� ��Ƽ���� ���� �����ؼ�, �� ��Ƽ�ǿ� ���� �������� �����Ѵ�. �� 16���� ��Ƽ�������� 8���� ��ó�� �������� ������.
* 
* <���� ���� �ڽ� Ŭ������ �߰��� ��>
* 1. ��ǥ 2���� 4���� ��Ƴ��� �迭. �׳� �ÿ��ϰ� 2���� �迭�ϳ� ������
* 2. �߰� ��ǥ�� ������ ���� Ȥ�� ����ؼ� ������ �Լ�.
* 
* �̰� ������ �̰ɷ� ����.
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
	srand(time(NULL));
	SetRect();

	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMainLoop(); // �̺�Ʈ ó�� ����
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
	glClearColor(mycolor.red, mycolor.green, mycolor.blue, mycolor.alpha); // �������� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�


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

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�


}

GLvoid Reshape(int w, int h) { //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� {
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

			//���⿡ 8��Ƽ�� �ÿ� [4]�ε�����[0]�� �迭 ���Ҹ� �ɰ��ִ� �ڵ� ��ֱ�

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