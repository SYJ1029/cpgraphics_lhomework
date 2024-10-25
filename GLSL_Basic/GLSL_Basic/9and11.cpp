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
#define MAX_INDEX12 18

GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid MyTimer(int index);
GLvoid MySpin(int index);
void swap(float* value1, float* value2);

MyCol mycolor = { 1.0f, 1.0f, 1.0f, 1.0f };
GLPos Screensize = { 800, 800, 0 };

float prevx, prevy;
float deltaX = 0, deltaY = 0;
int maxarray = 0;

MulandMove diagram[MAX_INDEX12];
GLRect Rect[4];

int polygonType = NO11_TOTRIANGLE;




void Setindex(int i, bool first) {
	int type = 0;

	if (first) {
		index_num = 0;
		index_array_count = 0;
	}

	type = diagram[i].Vertexcnt;

	if (type == 1) type = 3;



	for (int j = 0; j < 3; j++) {
		if (j >= 2 && type == 2)
			break;


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

	/*if (diagram[i].Vertexcnt == NO11_TOLINE) {
		index[index_num] = index_array_count - 5;
		index[index_num + 1] = index_array_count - 1;
		index[index_num + 2] = index_array_count;

		index_num += 3;
		index_array_count++;
	}*/



	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_DYNAMIC_DRAW);


}

int GetMaxArray() {
	for (int i = 0; i < MAX_INDEX12; i++) {
		if (diagram[i].maked == false)
			return i;
	}
}

MyObjCol SetRandObjCol() {
	MyObjCol coltoken = { (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX) };

	return coltoken;
}

bool SetRect() {
	MyObjCol coltoken[3] = { SetRandObjCol() , SetRandObjCol() , SetRandObjCol() };

	
	/*for (int i = 0; i < MAX_INDEX12; i++) {
		diagram[0]


		coltoken[0] = SetRandObjCol();
		coltoken[1] = SetRandObjCol();
		coltoken[2] = SetRandObjCol();

	}*/

	int token = 1;
	for (int i = 0; i < 18; i++) {
		token = token % 7;
		if (token == 0)
			token = 1;

		diagram[i].SetposType(token);
		diagram[i].SetPos({ (float)(rand()) / RAND_MAX * 2 - 1.0f, (float)(rand()) / RAND_MAX - 0.5f });

		coltoken[0] = SetRandObjCol();
		coltoken[1] = SetRandObjCol();
		coltoken[2] = SetRandObjCol();
		diagram[i].SetCol(coltoken);

		token++;
	}



	/*diagram[0].SetposType(NO11_TOTRIANGLE);
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
	diagram[3].SetposType(NO7_LINE);
	diagram[3].SetCol(coltoken);
	diagram[3].SetPos({ 0.5, -0.5 });

	coltoken[0] = SetRandObjCol();
	coltoken[1] = SetRandObjCol();
	coltoken[2] = SetRandObjCol();
	diagram[4].SetposType(NO11_TOLINE);
	diagram[4].SetCol(coltoken);
	diagram[4].SetPos({ 0.0, 0.0 });*/


	/*diagram[5].SetposType(NO11_TOTRIANGLE);
	diagram[5].SetPos({ -0.1, 0.1 });
	diagram[5].SetCol(coltoken);

	coltoken[0] = SetRandObjCol();
	coltoken[1] = SetRandObjCol();
	coltoken[2] = SetRandObjCol();
	diagram[6].SetposType(NO11_TORECT);
	diagram[6].SetPos({ 0.1, 0.1 });
	diagram[6].SetCol(coltoken);

	coltoken[0] = SetRandObjCol();
	coltoken[1] = SetRandObjCol();
	coltoken[2] = SetRandObjCol();
	diagram[7].SetposType(NO11_TOPENTAGON);
	diagram[7].SetCol(coltoken);
	diagram[7].SetPos({ -0.1, -0.1 });

	coltoken[0] = SetRandObjCol();
	coltoken[1] = SetRandObjCol();
	coltoken[2] = SetRandObjCol();
	diagram[8].SetposType(NO7_LINE);
	diagram[8].SetCol(coltoken);
	diagram[8].SetPos({ 0.1, -0.1 });

	coltoken[0] = SetRandObjCol();
	coltoken[1] = SetRandObjCol();
	coltoken[2] = SetRandObjCol();
	diagram[9].SetposType(NO11_TOLINE);
	diagram[9].SetCol(coltoken);
	diagram[9].SetPos({ 0.7, 0.7 });*/



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
	glutMotionFunc(Motion);
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
	bool first = true;

	for (int i = 0; i < MAX_INDEX12; i++) {
		if (diagram[i].maked) {
			type = diagram[i].GetposType();

			if (type == 6)
				cout << "6" << endl << endl;

			if (type == NO7_VERTEX)
				type = 3;

			for (int j = 0; j < type; j++) {


				glBufferSubData(GL_ARRAY_BUFFER, (*counter),
					3 * sizeof(GLfloat), diagram[i].Pos[j]);

				(*counter) += 3 * sizeof(GLfloat);


			}

			Setindex(i, first);
			first = false;


		}
	}



	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	(*counter) = 0;

	for (int i = 0; i < MAX_INDEX12; i++) {
		if (diagram[i].maked && i < MAX_INDEX12) {
			type = diagram[i].GetposType();
			if (type == NO7_VERTEX)
				type = 3;



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


			/*if (diagram[i].GetposType() >= NO11_TOLINE) {
				for (int j = 0; j < 2; j++) {
					glBufferSubData(GL_ARRAY_BUFFER, (*counter),
						3 * sizeof(GLfloat), diagram[i].col[j]);

					(*counter) += 3 * sizeof(GLfloat);
				}
			}*/

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

	for (int i = 0; i < MAX_INDEX12; i++) {
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


			/*if (token >= NO11_TOLINE)
				token = 5;*/

			int cnttoken = token;
			/*cnttoken = token + cnttoken * 2;*/

			/*if (cnttoken >= token)
				token = cnttoken;*/

			if (token == NO7_LINE)
				cout << "LINE!" << endl << endl;

			if (cnttoken < token)
				cnttoken = token;

			if (cnttoken == 1)
				cnttoken = 3;
			

			if (cnttoken == 2) {
				glDrawElements(ChangeValidType(cnttoken), (cnttoken),
					GL_UNSIGNED_INT, (void*)(drawcounter));

				drawcounter += (cnttoken) * sizeof(GLfloat);
			}

			for (int i = 0; i < cnttoken - 2; i++) {
				glDrawElements(ChangeValidType(cnttoken), 3,
					GL_UNSIGNED_INT, (void*)(drawcounter));

				drawcounter += 3 * sizeof(GLfloat);
			}



			/*glDrawElements(ChangeValidType(diagram[i].GetposType()), (diagram[i].GetposType()),
				GL_UNSIGNED_INT, (void*)(drawcounter));*/




			
			tricnt++;

			/*if (diagram[i].GetposType() == NO11_TOLINE) {
				glDrawElements(ChangeValidType(NO7_LINE), 2,
					GL_UNSIGNED_INT, (void*)(drawcounter));

				drawcounter += 2 * sizeof(GLfloat);
			}*/

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


GLPos GetBiggerDiagram(int index1, int index2) {
	float dist1 = diagram[index1].Pos[1][0] - diagram[index1].Pos[0][0];
	float dist2 = diagram[index2].Pos[1][0] - diagram[index2].Pos[0][0];


	if (dist1 >= dist2) return { (float)index1, (float)index2, 0 };

	return { (float)index2, (float)index1, 0 };
}


bool CheckDiagramIn(int index1, int index2) {
	for (int i = 0; i < diagram[index2].Vertexcnt; i++) {
		if (diagram[index1].CheckPosIn({ diagram[index2].Pos[i][0], diagram[index2].Pos[i][1] }))
			return true;

	}

	return false;
}


GLvoid Mouse(int button, int state, int x, int y) {
	GLPos newpos;
	bool mouseIn = false;
	MyObjCol coltoken[3] = { SetRandObjCol(), SetRandObjCol(), SetRandObjCol() };;

	if (state == GLUT_DOWN) {
		newpos = WintoGL(x, y, Screensize.x, Screensize.y);
		switch (button) {
		case GLUT_LEFT_BUTTON:
			for (int i = 0; i < MAX_INDEX12; i++) {
				if (diagram[i].maked && diagram[i].CheckPosIn(newpos)) {
					prevx = newpos.x;
					prevy = newpos.y;

					diagram[i].clicked = true;
				}
			}
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
		for (int i = 0; i < MAX_INDEX12; i++) {
			if (diagram[i].clicked) {
				diagram[i].clicked = false;

				for (int j = 0; j < MAX_INDEX12; j++) {
					if (diagram[j].maked && i != j) {
						GLPos token = GetBiggerDiagram(i, j);
						
						if (CheckDiagramIn((int)token.x, (int)token.y)) {
							diagram[j].SetNewDiagram(diagram[i].Vertexcnt);

							diagram[i].Clear();

						}


					}

				}

			}


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



GLvoid Motion(int x, int y) {
	GLPos postoken = WintoGL(x, y, Screensize.x, Screensize.y);

	float deltaX = postoken.x - prevx;
	float deltaY = postoken.y - prevy;

	for (int i = 0; i < MAX_INDEX12; i++) {
		if (diagram[i].clicked && diagram[i].maked) {
			diagram[i].MoveDrag(deltaX, deltaY, 0);

			prevx = postoken.x;
			prevy = postoken.y;
		}
	}


	glutPostRedisplay();
}