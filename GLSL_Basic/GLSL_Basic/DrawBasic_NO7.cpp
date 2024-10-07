#include "GetShader.h"

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid MyTimer(int index);
GLvoid MySpin(int index);

MyCol mycolor = { 1.0f, 1.0f, 1.0f, 1.0f };
GLPos Screensize = { 800, 800, 0 };

float prevx, prevy;
float deltaX = 0, deltaY = 0;
int maxarray = 0;



Diagram diagram[MAX_INDEX];
int polygonType = NO7_VERTEX;

void Setindex(int i) {
	int type = 0;

	if (i == 0) {
		index_num = 0;
		index_array_count = 0;
	}

	type = diagram[i].GetposType();

	if (type == 6) type -= 2;

	for (int j = 0; j < type; j++) {
		if (j >= 3) {
			index[index_num] = index[index_num - 3];
			index[index_num + 1] = index[index_num - 1];
			index[index_num + 2] = index_array_count;

			index_num += 3;
			index_array_count++;
			break;
		}

		index[index_num] = index_array_count;
		index_num++;
		index_array_count++;


	}




	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_DYNAMIC_DRAW);


}

int GetMaxArray() {
	for (int i = 0; i < MAX_INDEX; i++) {
		if (diagram[i].maked == false)
			return i;
	}
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

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop(); // 이벤트 처리 시작
}


GLvoid UpdateBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 18) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	float* counter = new FLOAT();
	(*counter) = 0;
	for (int i = 0; i < MAX_INDEX; i++) {
		if (diagram[i].maked) {
			for (int j = 0; j < diagram[i].GetposType(); j++) {


				glBufferSubData(GL_ARRAY_BUFFER, (*counter),
					3 * sizeof(GLfloat), diagram[i].pos[j]);

				(*counter) += 3 * sizeof(GLfloat);

				if (j > 2)
					break;
			}

			Setindex(i);


		}
	}



	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 12) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	(*counter) = 0;

	for (int i = 0; i < MAX_INDEX; i++) {
		if (diagram[i].maked && i < MAX_INDEX) {
			if (diagram[i].GetposType() == NO7_RECT);

			for (int j = 0; j < diagram[i].GetposType(); j++) {
				glBufferSubData(GL_ARRAY_BUFFER, (*counter),
					3 * sizeof(GLfloat), diagram[i].col[j]);

				(*counter) += 3 * sizeof(GLfloat);

				if (j > 2)
					break;
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
	glClearColor(mycolor.red, mycolor.green, mycolor.blue, mycolor.alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다

	glUseProgram(shaderProgramID);
	glBindVertexArray(vao);
	UpdateBuffer();

	int drawcounter = 0;
	int token = 0;

	for (int i = 0; i < MAX_INDEX; i++) {
		if (diagram[i].maked) {
			token = i - 1;
			if (token < 0)token = 0;


			/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);*/

			/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)((i * 9) * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);*/

			if (diagram[i].GetposType() == NO7_VERTEX)
				glPointSize(5.0);

			glDrawElements(ChangeValidType(diagram[i].GetposType()), (diagram[i].GetposType()),
				GL_UNSIGNED_INT, (void*)(drawcounter));

	

			drawcounter += (diagram[i].GetposType()) * sizeof(GLfloat);


			/*i* diagram[i].GetposType() * sizeof(GLfloat))*/
		}
	}


	glutSwapBuffers(); // 화면에 출력하기


}

GLvoid Reshape(int w, int h) { //--- 콜백 함수: 다시 그리기 콜백 함수 {
	glViewport(0, 0, w, h);
}



GLvoid Keyboard(unsigned char key, int x, int y) {

	maxarray = GetMaxArray();

	int randnum = (float)((float)rand() / RAND_MAX) * maxarray;

	while (diagram[randnum].deltax != 0.0 || diagram[randnum].deltay != 0.0 || diagram[randnum].deltaz != 0.0 ) {
		randnum = (float)((float)rand() / RAND_MAX) * maxarray;
	}

	switch (key) {
	case 'p':
		polygonType = NO7_VERTEX;
		break;
	case 'l':
		polygonType = NO7_LINE;
		break;
	case 't':
		polygonType = NO7_TRIANGLE;
		break;
	case 'r':
		polygonType = NO7_RECT;
		break;
	case 'c':
		for (int i = 0; i < MAX_INDEX; i++) {
			if (diagram[i].maked)
				diagram[i].Clear();
		}
		break;

	case 'w':
		diagram[randnum].SetDelta(0.0, 0.01, 0.0);
		glutTimerFunc(50, MyTimer, randnum);
		break;
	case 's':
		diagram[randnum].SetDelta(0.0, -0.01, 0.0);
		glutTimerFunc(50, MyTimer, randnum);
		break;
	case 'a':
		diagram[randnum].SetDelta(-0.01, 0.0, 0.0);
		glutTimerFunc(50, MyTimer, randnum);
		break;
	case 'd':
		diagram[randnum].SetDelta(0.01, 0.0, 0.0);
		glutTimerFunc(50, MyTimer, randnum);
		break;
	case 'g':
		diagram[randnum].SetRadian();
		glutTimerFunc(50, MySpin, randnum);
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

MyObjCol SetRandObjCol() {
	MyObjCol coltoken = { (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX) };

	return coltoken;
}

GLvoid Mouse(int button, int state, int x, int y) {
	GLPos newpos;
	bool mouseIn = false;
	MyObjCol coltoken[3] = { SetRandObjCol(), SetRandObjCol(), SetRandObjCol() };;

	if (state == GLUT_DOWN) {
		newpos = WintoGL(x, y, Screensize.x, Screensize.y);
		switch (button) {
		case GLUT_LEFT_BUTTON:
			for (int i = 0; i < MAX_INDEX; i++) {
				if (diagram[i].maked == false) {
					diagram[i].SetposType(polygonType);
					diagram[i].SetPos(newpos);
					diagram[i].SetCol(coltoken);
					break;
				}
			}
			

			/*if (ChangeRectPick(newpos) != -1) {
				prevx = newpos.x, prevy = newpos.y;

				break;
			}
			else {

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
			
		}
	}

	glutPostRedisplay();
}

GLvoid MyTimer(int index) {

	if (diagram[index].maked) {
		diagram[index].Move();
		glutTimerFunc(20, MyTimer, index);
	}

	glutPostRedisplay();
}


GLvoid MySpin(int index) {
	if (diagram[index].maked) {
		diagram[index].Spin();
		glutTimerFunc(100, MySpin, index);
	}

	glutPostRedisplay();
}