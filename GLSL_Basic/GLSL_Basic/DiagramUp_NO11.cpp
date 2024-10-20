#include "GetShader.h"


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
#define MAX_INDEX11 4

GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid MyTimer(int index);
GLvoid MySpin(int index);
void swap(float* value1, float* value2);

MyCol mycolor = { 1.0f, 1.0f, 1.0f, 1.0f };
GLPos Screensize = { 800, 800, 0 };

float prevx, prevy;
float deltaX = 0, deltaY = 0;
int maxarray = 0;

PlusDiagram diagram[MAX_INDEX11];
GLRect Rect[4];

int polygonType = NO11_TOTRIANGLE;




void Setindex(int i) {
	int type = 0;

	if (i == 0) {
		index_num = 0;
		index_array_count = 0;
	}

	type = diagram[i].Vertexcnt;

	if (type == 6) type = 5;


	index[index_num] = index_array_count;
	index[index_num + 1] = index_array_count + 1;
	index_num += 2;


	for (int j = 0; j < type; j++) {
		if (j >= 3) {
			/*index[index_num] = index[index_num - 3];
			index[index_num + 1] = index[index_num - 1];
			index[index_num + 2] = index_array_count;

			index_num += 3;
			index_array_count++;*/
			break;
		}

		index[index_num] = index_array_count;
		index_num++;
		index_array_count++;


	}
	
	int token = index_num - 3;
	for (int i = NO11_TOTRIANGLE; i < type; i++) {
		index[index_num] = index[token];
		index[index_num + 1] = index[index_num - 1];
		index[index_num + 2] = index_array_count;

		index_num += 3;
		index_array_count++;
	}

	if (diagram[i].Vertexcnt == NO11_TOLINE) {
		index[index_num] = index_array_count - 5;
		index[index_num + 1] = index_array_count - 1;

		index_num += 2;
	}



	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_DYNAMIC_DRAW);


}

int GetMaxArray() {
	for (int i = 0; i < MAX_INDEX11; i++) {
		if (diagram[i].maked == false)
			return i;
	}
}

MyObjCol SetRandObjCol() {
	MyObjCol coltoken = { (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX) };

	return coltoken;
}

bool SetRect() {
	Rect[0].pos1 = { -1, 1 };
	Rect[0].pos2 = { 0, 0 };
	Rect[0].max = 3;
	Rect[0].cnt = 1;

	Rect[1].pos1 = { 0, 1 };
	Rect[1].pos2 = { 1, 0 };
	Rect[1].max = 3;
	Rect[1].cnt = 1;

	Rect[2].pos1 = { -1, 0 };
	Rect[2].pos2 = { 0, -1 };
	Rect[2].max = 3;
	Rect[2].cnt = 1;

	Rect[3].pos1 = { 0, 0 };
	Rect[3].pos2 = { 1, -1 };
	Rect[3].max = 3;
	Rect[3].cnt = 1;



	MyObjCol coltoken[3] = { SetRandObjCol() , SetRandObjCol() , SetRandObjCol() };

	diagram[0].SetposType(NO11_TOTRIANGLE);
	diagram[0].SetPos({ -0.5, 0.5 });
	diagram[0].SetCol(coltoken);

	coltoken[0] = SetRandObjCol();
	coltoken[1] = SetRandObjCol();
	coltoken[2] = SetRandObjCol();
	diagram[1].SetposType(NO11_TORECT);
	diagram[1].SetPos({ 0.5, 0.5 });
	diagram[1].SetCol(coltoken);

	coltoken[0] = SetRandObjCol();
	coltoken[1] = SetRandObjCol();
	coltoken[2] = SetRandObjCol();
	diagram[2].SetposType(NO11_TOPENTAGON);
	diagram[2].SetCol(coltoken);
	diagram[2].SetPos({ -0.5, -0.5 });

	coltoken[0] = SetRandObjCol();
	coltoken[1] = SetRandObjCol();
	coltoken[2] = SetRandObjCol();
	diagram[3].SetposType(NO11_TOLINE);
	diagram[3].SetCol(coltoken);
	diagram[3].SetPos({ 0.5, -0.5 });

	return true;
}

void main(int argc, char** argv) { //--- ������ ����ϰ� �ݹ��Լ� ���� { //--- ������ �����ϱ�
	srand(time(NULL));

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

	make_vertexShaders();
	make_fragmentShaders();
	make_shaderProgram();
	InitBuffer();
	SetRect();

	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop(); // �̺�Ʈ ó�� ����
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
	for (int i = 0; i < MAX_INDEX11; i++) {
		if (diagram[i].maked) {
			type = diagram[i].GetposType();

			if (type == NO11_TOLINE)
				type = 5;

			for (int j = 0; j < type; j++) {


				glBufferSubData(GL_ARRAY_BUFFER, (*counter),
					3 * sizeof(GLfloat), diagram[i].Pos[j]);

				(*counter) += 3 * sizeof(GLfloat);

				
			}

			Setindex(i);


		}
	}



	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	(*counter) = 0;

	for (int i = 0; i < MAX_INDEX11; i++) {
		if (diagram[i].maked && i < MAX_INDEX11) {
			type = diagram[i].GetposType();
			if (type == NO11_TOLINE)
				type = 5;

			

			/*for (int j = 0; j < 2; j++) {
				glBufferSubData(GL_ARRAY_BUFFER, (*counter),
					3 * sizeof(GLfloat), diagram[i].col[j]);

				(*counter) += 3 * sizeof(GLfloat);
			}*/


			for (int j = 0; j < type; j++) {
				glBufferSubData(GL_ARRAY_BUFFER, (*counter),
					3 * sizeof(GLfloat), diagram[i].col[j]);

				(*counter) += 3 * sizeof(GLfloat);

			
			}


			if (diagram[i].GetposType() >= NO11_TOLINE) {
				for (int j = 0; j < 2; j++) {
					glBufferSubData(GL_ARRAY_BUFFER, (*counter),
						3 * sizeof(GLfloat), diagram[i].col[j]);

					(*counter) += 3 * sizeof(GLfloat);
				}
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�

	glUseProgram(shaderProgramID);
	glBindVertexArray(vao);
	UpdateBuffer();

	int drawcounter = 0;
	int token = 0;
	int tricnt = 0;

	for (int i = 0; i < MAX_INDEX11; i++) {
		if (diagram[i].maked) {
			


			/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);*/

			/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)((i * 9) * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);*/


			/*if (diagram[i].GetposType() == NO7_LINE) {

				for (int j = 0; j < 2; j++) {
					glDrawElements(ChangeValidType(diagram[i].GetposType()), (diagram[i].GetposType()),
						GL_UNSIGNED_INT, (void*)(drawcounter));
					drawcounter += (diagram[i].GetposType()) * sizeof(GLfloat);
				}

			}*/

			if (diagram[i].GetposType() >= NO11_TOTRIANGLE) {
			}


			token = diagram[i].GetposType();


			if (token >= NO11_TOLINE)
				token = 5;

			int cnttoken = token - 3;
			cnttoken = token + cnttoken * 2;

			glDrawElements(ChangeValidType(NO7_LINE), 2,
				GL_UNSIGNED_INT, (void*)(drawcounter));

			drawcounter += 2 * sizeof(GLfloat);

		

			glDrawElements(ChangeValidType(diagram[i].GetposType()), (cnttoken),
				GL_UNSIGNED_INT, (void*)(drawcounter));

		
			
			/*glDrawElements(ChangeValidType(diagram[i].GetposType()), (diagram[i].GetposType()),
				GL_UNSIGNED_INT, (void*)(drawcounter));*/




			drawcounter += (cnttoken) * sizeof(GLfloat);
			tricnt++;

			if (diagram[i].GetposType() == NO11_TOLINE) {
				glDrawElements(ChangeValidType(NO7_LINE), 2,
					GL_UNSIGNED_INT, (void*)(drawcounter));

				drawcounter += 2 * sizeof(GLfloat);
			}

			/*i* diagram[i].GetposType() * sizeof(GLfloat))*/
		}
	}
	cout << "�ﰢ�� ��: " << tricnt << endl << endl;

	cout << "<��и� ����>" << endl << endl;

	for (int i = 0; i < 4; i++) {
		cout << i + 1 << ") tri:  " << Rect[i].cnt << "    max: " << Rect[i].max << endl;
	}

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�


}

GLvoid Reshape(int w, int h) { //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� {
	glViewport(0, 0, w, h);
}





GLvoid Keyboard(unsigned char key, int x, int y) {

	maxarray = GetMaxArray();

	int randnum = (float)((float)rand() / RAND_MAX) * maxarray;

	/*while (diagram[randnum].deltax != 0.0 || diagram[randnum].deltay != 0.0 || diagram[randnum].deltaz != 0.0) {
		randnum = (float)((float)rand() / RAND_MAX) * maxarray;
	}*/

	switch (key) {
	case 'l':
		
		glutTimerFunc(10, MyTimer, 0);
		break;
	case 't':
		glutTimerFunc(10, MyTimer, 1);
		break;
	case 'r':
		/*Myswap(&(diagram[2].Pos[3][0]), &(diagram[2].Pos[4][0]));
		Myswap(&(diagram[2].Pos[3][1]), &(diagram[2].Pos[4][1]));*/
		

		glutTimerFunc(10, MyTimer, 2);
		break;
	case 'p':
		// ���� ��ȯ �ÿ� 3�ε����� 4�ε��� �� ���� �ٲ���� �Ѵ�.


		glutTimerFunc(10, MyTimer, 3);
		break;

	case 'a':
		SetRect();
		glutTimerFunc(10, MyTimer, 0);
		glutTimerFunc(10, MyTimer, 1);
		glutTimerFunc(10, MyTimer, 2);
		glutTimerFunc(10, MyTimer, 3);


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
//	for (int i = MAX_INDEX11 - 1; i >= 0; i--) {
//		if (diagram[i].maked)
//			if (CheckMounseIn(newPos, i, diagram[i].pos)) {
//				return i;
//			}
//
//	}
//
//	return 1;
//}

//bool Allclear(int index) {
//	for (int i = 0; i < MAX_INDEX11; i++) {
//
//		if (diagram[i].maked) {
//			if (IsPosInRect(diagram[i].GetCenter(), Rect[index].pos1, Rect[index].pos2)) {
//				diagram[i].Clear();
//			}
//
//		}
//	}
//
//	Rect[index].cnt = 0;
//	return true;
//}


GLvoid Mouse(int button, int state, int x, int y) {
	GLPos newpos;
	bool mouseIn = false;
	MyObjCol coltoken[3] = { SetRandObjCol(), SetRandObjCol(), SetRandObjCol() };;

	if (state == GLUT_DOWN) {
		newpos = WintoGL(x, y, Screensize.x, Screensize.y);
		switch (button) {
		case GLUT_LEFT_BUTTON:

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
		for (int i = 0; i < MAX_INDEX11; i++) {

		}
	}

	glutPostRedisplay();
}



GLvoid MyTimer(int index) {

	if (diagram[index].Spin()) {
		glutTimerFunc(10, MyTimer, index);
	}



	glutPostRedisplay();
}