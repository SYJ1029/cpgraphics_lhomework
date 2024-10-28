#include "Head/3DDiagram.h"

#define MAX_INDEX 12
#define MAX_INDEX13 2

#define ID_CUBE 0
#define ID_TET 1
#define ID_PYR 2
#define ID_SPHERE 3
#define ID_

GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid MyCcw(int value);
GLvoid MyCw(int value);
GLvoid specialKeyboard(int key, int x, int y);



MyCol mycolor = { 1.0f, 1.0f, 1.0f, 1.0f };
GLPos Screensize = { 800, 800, 0 };
GL_Cube* cube = new GL_Cube;
GL_Tetrahedron* tri = new GL_Tetrahedron;
GL_Pyramid* pyr = new GL_Pyramid;

Diagram playground[2];


bool depthed = true;
bool gospin = false;
bool direct = true;


GLfloat base_axis[6][3] = {
	-1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, 1.0f
};

GLfloat base_axis_col[6][3] = {
	1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

int baseAxisIndex = 0;


GLvoid Setplayground() {

	playground[0].center = { -3.0f, 0.0f, 0.0f };
	playground[1].center = { 3.0f, 0.0f, 0.0f };

	playground[0].radian = 0;
	playground[1].radian = 0;

	playground[0].Stretch = { 0.2f, 0.2f, 0.2f };
	playground[1].Stretch = { 0.2f, 0.2f, 0.2f };

	playground[0].postype = ID_CUBE;
	playground[1].postype = ID_PYR;
}

void DepthCheck() {
	if (depthed)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void Setindex() {
	int* p1 = cube->AddIndexList();
	int* p2 = tri->AddIndexList();
	int* p3 = pyr->AddIndexList();

	cout << sizeof((p1));

	int present_bit = index_count;
	int cnt = 0;
	int begin = cnt;




	for (index_count; index_count < 36; index_count++) {
		index[index_count] = p1[index_count];

		cnt++;
	}

	cube->start_index = 0;
	//cnt += 36;

	present_bit = index_count;

	begin = cnt;

	tri->start_index = index_count;

	for (index_count; index_count < present_bit + 12; index_count++) {
		index[index_count] = 8 + p2[index_count - begin];

		cnt++;
	}

	//cnt += 12;

	present_bit = index_count;
	begin = cnt;

	pyr->start_index = index_count;

	for (index_count; index_count < present_bit + 18; index_count++) {
		index[index_count] = 12 + p3[index_count - begin];
	}

	cnt += 15;


	present_bit = index_count;
	baseAxisIndex = index_count;

	for (index_count; index_count < present_bit + 6; index_count++, index_array_count++) {
		index[index_count] = 12 + 5 + index_array_count;
	}



	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_DYNAMIC_DRAW);

	free(p1);
	free(p2);
	free(p3);
}

MyObjCol SetRandObjCol() {
	MyObjCol coltoken = { (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX), (float)((float)rand() / RAND_MAX) };

	return coltoken;
}

GLvoid SetBuffer() {
	MyObjCol mycol[8];
	MyObjCol mycol2[4];
	MyObjCol mycol3[5];

	for (int i = 0; i < 8; i++) {
		mycol[i] = SetRandObjCol();
	}
	for (int i = 0; i < 4; i++) {
		mycol2[i] = SetRandObjCol();
	}
	for (int i = 0; i < 5; i++) {
		mycol3[i] = SetRandObjCol();
	}
	cube->Setcol(mycol);
	tri->Setcol(mycol2);
	pyr->Setcol(mycol3);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	cube->SetPos();
	tri->SetPos();
	pyr->SetPos();

	//float* counter = new FLOAT();
	int* counter = new INT();
	(*counter) = 0;
	int type = 0;




	for (int i = 0; i < 8; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), cube->pos[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}


	for (int i = 0; i < 4; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), tri->pos[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}

	for (int i = 0; i < 5; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), pyr->pos[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}



	for (int i = 0; i < 6; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), base_axis[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}

	/*index_count = 0;
	index_array_count = 0;*/

	Setindex();



	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);




	(*counter) = 0;


	for (int i = 0; i < 8; i++) {


		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), cube->col[i]);

		(*counter) += 3 * sizeof(GLfloat);

		//cout << "(" << cube.pos[i][0] << ", " << cube.pos[i][1] << ", " << cube.pos[i][2] << ')' << endl << endl;
	}

	for (int i = 0; i < 4; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), tri->col[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}

	for (int i = 0; i < 5; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), pyr->col[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}




	for (int i = 0; i < 6; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), base_axis_col[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}





void main(int argc, char** argv) { //--- 윈도우 출력하고 콜백함수 설정 { //--- 윈도우 생성하기
	srand(time(NULL));

	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
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


	glBindVertexArray(vao);
	SetBuffer();
	Setplayground();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);


	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(specialKeyboard);
	glutMouseFunc(Mouse);



	glutMainLoop(); // 이벤트 처리 시작


}


void drawCube(float* counter, int index) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);


}

float radian = 10.0f;
int mycnt = 0;
glm::vec3 allAxis = glm::vec3(0.0f, 0.0f, 0.0f);

void drawScene()
{
	Diagram* drawStage = nullptr;

	drawStage = cube;


	glClearColor(mycolor.red, mycolor.green, mycolor.blue, mycolor.alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//gluLookAt(0.0, 0.0, 100.0f, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glUseProgram(shaderProgramID);
	glm::mat4 basemat = glm::mat4(1.0f);
	glm::mat4 rm = basemat;
	glm::mat4 rm2 = basemat;
	glm::mat4 model = basemat;
	//glm::mat4 rm3 = glm::mat4(1.0f);

	/*model = glm::translate(model, glm::vec3(0.1f, 0.5f, 0.0f));*/
	int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform");

	glBindVertexArray(vao);




	int counter = 0;



	for (int i = 0; i < 2; i++) {



		rm = glm::rotate(basemat, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		rm2 = glm::rotate(basemat, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		model = rm2 * rm;

		model *= GetMove(playground[i].center);
		model *= GetSpin(playground[i].center, playground[i].radian, playground[i].axis);
		model *= ChangeScale(playground[i].Stretch, playground[i].center);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));


		if (playground[i].postype == ID_CUBE) {

			glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, (void*)(cube->start_index * sizeof(GLfloat)));
		}

		if (playground[i].postype == ID_PYR) {
			glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, (void*)(pyr->start_index * sizeof(GLfloat)));
		}

		model = basemat;
	}









	model = basemat;

	rm = glm::rotate(basemat, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	rm2 = glm::rotate(basemat, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	model = rm2 * rm;

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, (void*)(baseAxisIndex * sizeof(GLfloat)));
	counter += 6 * sizeof(GLint);




	glutSwapBuffers();

}

GLvoid Reshape(int w, int h) { //--- 콜백 함수: 다시 그리기 콜백 함수 {
	glViewport(0, 0, w, h);
}


GLvoid Mouse(int button, int state, int x, int y) {


	glutPostRedisplay();
}




GLvoid Keyboard(unsigned char key, int x, int y) {

	int token = (int)key - (int)'1';
	int randnum[2];
	randnum[0] = -1, randnum[1] = -1;

	switch (key) {
	case 'c':
		for (int i = 0; i < 6; i++) {
			if (i < 4) {
				tri->maked[i] = false;
			}

			if (i < 5) {
				pyr->maked[i] = false;
			}

			cube->maked[i] = true;
		}


		break;
	case 't':
		for (int i = 0; i < 6; i++) {
			if (i < 4) {
				tri->maked[i] = true;
			}

			if (i < 5) {
				pyr->maked[i] = false;
			}

			cube->maked[i] = false;
		}

		break;

	case 'p':
		for (int i = 0; i < 6; i++) {
			if (i < 4) {
				tri->maked[i] = false;
			}

			if (i < 5) {
				pyr->maked[i] = true;
			}

			cube->maked[i] = false;
		}
		break;
	case 'h':
		depthed = !(depthed);
		DepthCheck();
		break;

	case 'w': case 'W':
		if ((int)key - (int)'a' < 0) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		}

		break;

	case 'x': case 'X':
		gospin = true;

		if ((int)key - (int)'a' < 0) {
			direct = true;

			cube->axis = glm::vec3(1.0f, 0.0f, 0.0f);
			tri->axis = glm::vec3(1.0f, 0.0f, 0.0f);
			pyr->axis = glm::vec3(1.0f, 0.0f, 0.0f);
			glutTimerFunc(10, MyCcw, 0);
		}
		else {
			direct = false;

			cube->axis = glm::vec3(1.0f, 0.0f, 0.0f);
			tri->axis = glm::vec3(1.0f, 0.0f, 0.0f);
			pyr->axis = glm::vec3(1.0f, 0.0f, 0.0f);
			glutTimerFunc(10, MyCw, 0);
		}

		break;
	case 'y': case 'Y':
		gospin = true;

		if ((int)key - (int)'a' < 0) {
			direct = true;

			cube->axis = glm::vec3(0.0f, 1.0f, 0.0f);
			tri->axis = glm::vec3(0.0f, 1.0f, 0.0f);
			pyr->axis = glm::vec3(0.0f, 1.0f, 0.0f);
			glutTimerFunc(10, MyCcw, 0);
		}
		else {
			direct = false;

			cube->axis = glm::vec3(0.0f, 1.0f, 0.0f);
			tri->axis = glm::vec3(0.0f, 1.0f, 0.0f);
			pyr->axis = glm::vec3(0.0f, 1.0f, 0.0f);
			glutTimerFunc(10, MyCw, 0);

		}

		break;
	case 's':
		gospin = false;
		cube->center = { 0 };
		tri->center = { 0 };
		pyr->center = { 0 };
		break;



	case 'q':

		delete cube;
		delete tri;
		delete pyr;
		glutLeaveMainLoop();
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

GLvoid specialKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		cube->center.x -= 0.02f;
		tri->center.x -= 0.02f;
		pyr->center.x -= 0.02f;
		break;
	case GLUT_KEY_RIGHT:
		cube->center.x += 0.02f;
		tri->center.x += 0.02f;
		pyr->center.x += 0.02f;
		break;
	case GLUT_KEY_UP:
		cube->center.y += 0.02f;
		tri->center.y += 0.02f;
		pyr->center.y += 0.02f;
		break;
	case GLUT_KEY_DOWN:
		cube->center.y -= 0.02f;
		tri->center.y -= 0.02f;
		pyr->center.y -= 0.02f;
		break;
	}

	glutPostRedisplay();
}



GLvoid MyCcw(int value) {

	radian += 5;


	if (gospin && direct) {
		glutTimerFunc(10, MyCcw, value);
	}
	glutPostRedisplay();
}
GLvoid MyCw(int value) {

	radian -= 5;


	if (gospin && direct == false) {
		glutTimerFunc(10, MyCw, value);
	}
	glutPostRedisplay();
}