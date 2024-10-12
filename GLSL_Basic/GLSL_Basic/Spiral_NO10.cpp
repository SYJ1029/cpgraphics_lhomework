#include "Triangle.h"

using namespace std;

typedef struct GLRECT {
	GLPos pos1;
	GLPos pos2;
	int max;
	int cnt;
}GLRect;


#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid MyTimer(int index);
GLvoid MySpin(int index);

MyCol mycolor = { 1.0f, 0.0f, 0.0f, 1.0f };
GLPos Screensize = { 800, 800, 0 };

float prevx, prevy;
float deltaX = 0, deltaY = 0;
int maxarray = 0;
int randnum[MAX_INDEX10];
int timenum[MAX_INDEX10] = { 0 };

Spiral Vertex[MAX_INDEX10];
//TriAnimation diagram[MAX_INDEX];
GLRect Rect[4];

int polygonType = TYPE_DOT;




void Setindex(int i, bool first, int c) {
	int type = Vertex[i].GetposType();

	if (i == 0 && first) {
		index_num = 0;
		index_array_count = 0;
	}



	index[index_num] = index_array_count;
	index_num++;
	if (type == TYPE_LINE && c > 0 && c < 279 && c < Vertex[i].cnt - 1) {
		index[index_num] = index_array_count;
		index_num++;
	}
	index_array_count++;






	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_DYNAMIC_DRAW);


}

int GetMaxArray() {
	for (int i = 0; i < MAX_INDEX10; i++) {
		if (Vertex[i].maked == false)
			return i;
	}
}

MyObjCol SetRandObjCol() {
	MyObjCol coltoken = { (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX) };

	return coltoken;
}



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

	make_vertexShaders();
	make_fragmentShaders();
	make_shaderProgram();
	InitBuffer();
	/*SetRect();*/

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop(); // 이벤트 처리 시작
}


bool IsPosInRect(GLPos mouse, GLPos pos1, GLPos pos4) {
	GLPos pos2 = { pos4.x, pos1.y };
	GLPos pos3 = { pos1.x, pos4.y };

	if (mouse.x >= pos1.x && mouse.x <= pos4.x
		&& mouse.y >= pos4.y && mouse.y <= pos1.y)
		return true;


	return false;
}

GLvoid UpdateBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	float* counter = new FLOAT();
	(*counter) = 0;
	int type = 0;
	bool first = true;

	for (int i = 0; i < MAX_INDEX10; i++) {
		if (Vertex[i].maked) {
			type = Vertex[i].GetposType();

			for (int c = 0; c < Vertex[i].cnt; c++) {
				if (Vertex[i].nowcnt >= 280)
					break;


				/*if (Vertex[i].radian >= Vertex[i].cnt) {
					Vertex[i].Revert();
					Vertex[i].cnt++;
				}*/


				glBufferSubData(GL_ARRAY_BUFFER, (*counter),
					3 * sizeof(GLfloat), Vertex[i].pos);


				(*counter) += 3 * sizeof(GLfloat);


				Setindex(i, first, c);
				

				Vertex[i].Move();
				first = false;

			}

			//cout << Vertex[i].cnt << endl << endl;
			Vertex[i].Revert();
		}
	}

	



	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	(*counter) = 0;

	for (int i = 0; i < MAX_INDEX10; i++) {
		if (Vertex[i].maked && i < MAX_INDEX10) {

			for (int c = 0; c < Vertex[i].cnt; c++) {
				if (Vertex[i].nowcnt >= 280)
					break;

				glBufferSubData(GL_ARRAY_BUFFER, (*counter),
					3 * sizeof(GLfloat), Vertex[i].col);

				(*counter) += 3 * sizeof(GLfloat);

			}
		}
	}
	

	//glEnableVertexAttribArray(1);





	/*glDrawElements(GL_TRIANGLES, (drawcounter),
		GL_UNSIGNED_INT, 0);*/


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

GLvoid drawScene() {
	int drawcounter = 0;

	glClearColor(mycolor.red, mycolor.green, mycolor.blue, mycolor.alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다

	glUseProgram(shaderProgramID);
	glBindVertexArray(vao);
	UpdateBuffer();


	for (int i = 0; i < MAX_INDEX10; i++) {
		
		if (Vertex[i].maked) {

			/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);*/

			/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)((i * 9) * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);*/

			if (Vertex[i].GetposType() == TYPE_DOT)
				glPointSize(2.0);

			/*if (Vertex[i].GetposType() == TYPE_LINE) {

				glDrawElements(ChangeValidType(Vertex[i].GetposType()), (Vertex[i].GetposType()),
					GL_UNSIGNED_INT, (void*)(drawcounter));
				drawcounter += (Vertex[i].GetposType()) * sizeof(GLfloat);


			}*/


			for (int c = 0; c < Vertex[i].cnt - 1; c++) {
				if (Vertex[i].nowcnt >= 280)
					break;
				glDrawElements(ChangeValidType(Vertex[i].GetposType()), (Vertex[i].GetposType()),
					GL_UNSIGNED_INT, (void*)(drawcounter));

				drawcounter += (Vertex[i].GetposType()) * sizeof(GLfloat);
			}

			/*i* diagram[i].GetposType() * sizeof(GLfloat))*/
		}

		timenum[i] = 0;
	}



	glutSwapBuffers(); // 화면에 출력하기


}

GLvoid Reshape(int w, int h) { //--- 콜백 함수: 다시 그리기 콜백 함수 {
	glViewport(0, 0, w, h);
}



GLvoid Keyboard(unsigned char key, int x, int y) {
	GLPos newpos = { 0, 0, 0 };
	maxarray = GetMaxArray();

	int token = 0;
	float ccw = 0;
	switch (key) {
	case '1':case '2':case '3':case '4':case '5':
		for (int i = 0; i < MAX_INDEX10; i++) {
			Vertex[i].Clear();
		}

		for (int i = 0; i < 5000; i++) {
			index[i] = 0;
		}

		token = (int)key - (int)'0';
		for (int i = 0; i < token; i++) {
			ccw = (float)rand() / RAND_MAX * 100;
			newpos.x = (float)(((float)rand() / RAND_MAX) * 600 + 100);
			newpos.y = (float)(((float)rand() / RAND_MAX) * 600 + 100);
			newpos.z = 0;
			newpos = WintoGL(newpos.x, newpos.y, Screensize.x, Screensize.y);

			randnum[i] = (float)((float)rand() / RAND_MAX) * 10 + 30;
			Vertex[i].SetposType(polygonType);
			Vertex[i].SetPos(newpos);
			Vertex[i].SetCol({ 1.0f, 1.0f, 1.0f });
			if(ccw > 50)
				Vertex[i].Settheta(basetheta);
			else
				Vertex[i].Settheta(basetheta * -1);
			Vertex[i].maked = true;

			glutTimerFunc(randnum[i], MyTimer, i);
		}
		break;
	case 'p':
		polygonType = TYPE_DOT;
		break;
	case 'l':
		polygonType = TYPE_LINE;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}


bool ChangeWindowCol() {
	mycolor = { (float)((float)rand() / RAND_MAX), 	(float)((float)rand() / RAND_MAX), 	(float)((float)rand() / RAND_MAX), 1.0f };

	return true;
}

//int ChangeRectPick(GLPos newPos) {
//
//	for (int i = MAX_INDEX - 1; i >= 0; i--) {
//		if (diagram[i].maked)
//			if (CheckMounseIn(newPos, i, diagram[i].pos)) {
//				return i;
//			}
//
//	}
//
//	return 1;
//}

bool Allclear(int index) {
	for (int i = 0; i < MAX_INDEX10; i++) {

		if (Vertex[i].maked) {
			Vertex[i].Clear();
		}
	}

	Rect[index].cnt = 0;
	return true;
}


GLvoid Mouse(int button, int state, int x, int y) {
	GLPos newpos;
	bool mouseIn = false;
	MyObjCol coltoken[3] = { SetRandObjCol(), SetRandObjCol(), SetRandObjCol() };
	float ccw = (float)rand() / RAND_MAX * 100;

	if (state == GLUT_DOWN) {
		newpos = WintoGL(x, y, Screensize.x, Screensize.y);
		switch (button) {
		case GLUT_LEFT_BUTTON:


			for (int i = 0; i < MAX_INDEX10; i++) {
				Vertex[i].Clear();
			}

			for (int i = 0; i < 5000; i++) {
				index[i] = 0;
			}

			randnum[0] = (float)((float)rand() / RAND_MAX) * 10 + 20;
			Vertex[0].SetposType(polygonType);
			Vertex[0].SetPos(newpos);
			Vertex[0].SetCol({ 1.0f, 1.0f, 1.0f });
			if(ccw > 50)
				Vertex[0].Settheta(basetheta);
			else
				Vertex[0].Settheta(basetheta * -1);

			Vertex[0].maked = true;

			glutTimerFunc(randnum[0], MyTimer, 0);



			break;
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

		}
	}

	glutPostRedisplay();
}


GLvoid MyTimer(int index) {

	//cout << "<<< " << index + 1 << "번지에서 >>>" << endl << endl << endl;
	/*Vertex[index].Move();
	glutTimerFunc(randnum[index], MyTimer, index);*/

	if (Vertex[index].maked && timenum[index] <= 0) {
		Vertex[index].cnt++;
		glutTimerFunc(randnum[index], MyTimer, index);
		timenum[index]++;
	}

	glutPostRedisplay();

}