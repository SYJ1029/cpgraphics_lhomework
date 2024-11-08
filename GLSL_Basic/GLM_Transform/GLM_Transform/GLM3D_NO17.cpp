#pragma once

#include "Head/LoadDiagram.h"

Camera* camera;
Projection* proj;

#define MAX_INDEX 12
#define MAX_INDEX13 2

#define ID_CUBE 0
#define ID_TET 1
#define ID_PYR 2
#define ID_SPHERE 3
#define ID_CYLINDER 4
#define ID_CONE 5


GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid MyCcw(int value);
GLvoid MyCw(int value);
GLvoid OrbitCcw(int value);
GLvoid OrbitCw(int value);
GLvoid specialKeyboard(int key, int x, int y);
GLvoid MyLineMove(int value);
GLvoid MyStretch(int value);
GLvoid MySpiralCw(int value);
GLvoid MySpiralCcw(int value);



Diagram playground;


bool depthed = true;
bool gospin[2] = { false, false };
bool direct = true;
bool goorbit = false;
bool endorbit = false;
bool checkPoint = false;
bool goStretch = false;
bool goSpiral = false;


float base_axis[6][3] = {
	-1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, 1.0f
};

float base_axis_col[6][3] = {
	1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

int baseAxisIndex = 0;


GLvoid Setplayground() {

	playground.center = { 0.0f, 0.0f, 0.0f };

	playground.radian = { 0.0f, 0.0f, 0.0f };

	playground.Stretch = { 0.2f, 0.2f, 0.2f };

	playground.Orbit = { 0.0f, 0.0f, 0.0f };

	playground.postype = ID_CUBE;
}


GLvoid SetCamera() {

	camera = new Camera(glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
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
	SetCamera();
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

		gluQuadricDrawStyle(qobj, playground.qset.drawstyle);
		gluQuadricNormals(qobj, playground.qset.normals);
		gluQuadricOrientation(qobj, playground.qset.orientation);

		/*rm = glm::rotate(basemat, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		rm2 = glm::rotate(basemat, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/

		model = rm2 * rm;

		model *= InitRotateProj(playground.Orbit, { 0.0f, 0.0f, 0.0f });
		model *= InitRotateProj(playground.radian, playground.center);
		model *= InitMoveProj(playground.center);
		model *= InitScaleProj(playground.Stretch);




		glm::mat4 view = glm::mat4(1.0);

		view = camera->GetViewMatix();

		unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		switch (playground.postype) {
		case ID_CUBE:
			glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, (void*)(cube->start_index * sizeof(GLfloat)));
			break;
		case ID_TET:
			glDrawElements(GL_TRIANGLES, 3 * 4, GL_UNSIGNED_INT, (void*)(tri->start_index * sizeof(GLfloat)));
			break;
		case ID_PYR:
			glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, (void*)(pyr->start_index * sizeof(GLfloat)));
			break;
		case ID_SPHERE:
			gluSphere(qobj, sphere->radius, sphere->slices, sphere->stacks);
			break;
		case ID_CYLINDER:
			gluCylinder(qobj, 1.0, 1.0, 2.0, 20, 8);
			break;
		case ID_CONE:
			gluCylinder(qobj, 1.0, 0.0, 2.0, 20, 8);
			break;
		}

		model = basemat;
	}







	model = basemat;

	/*rm = glm::rotate(basemat, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	rm2 = glm::rotate(basemat, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/

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
	int mulcount = -1;
	GLPos firstttoken = { 0.0f, 0.8f, 0.0f };

	switch (key) {
	case 'h':
		depthed = !(depthed);
		DepthCheck();
		break;

	case 'w': case 'W':
		if ((int)key - (int)'a' < 0) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			for (int i = 0; i < 2; i++) {
				playground.qset.drawstyle = GLU_FILL;
			}

		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			for (int i = 0; i < 2; i++) {
				playground.qset.drawstyle = GLU_LINE;
			}
		}

		break;

	case 'x': case 'X':
		gospin[0] = true;
		gospin[1] = true;

		playground.axis = glm::vec3(1.0f, 0.0f, 0.0f);
		

		if ((int)key - (int)'a' < 0) {
			direct = true;


			glutTimerFunc(10, MyCcw, 0);
			glutTimerFunc(10, MyCcw, 1);
		}
		else {
			direct = false;
			glutTimerFunc(10, MyCw, 0);
			glutTimerFunc(10, MyCw, 1);
		}

		break;
	case 'y': case 'Y':
		gospin[0] = true;
		gospin[1] = true;

		playground.axis = glm::vec3(0.0f, 1.0f, 0.0f);
		

		if ((int)key - (int)'a' < 0) {
			direct = true;

			glutTimerFunc(10, MyCcw, 0);
			glutTimerFunc(10, MyCcw, 1);
		}
		else {
			direct = false;

			glutTimerFunc(10, MyCw, 0);
			glutTimerFunc(10, MyCw, 1);
		}

		break;
	case 'r': case 'R':
		goStretch = false;
		goorbit = true;

		if ((int)key - (int)'a' < 0) {
			playground.orbitccw = true;
			glutTimerFunc(10, OrbitCcw, 0);

		}
		else {
			playground.orbitccw = false;
			glutTimerFunc(10, OrbitCw, 0);

		}

		break;
	case 's':
		goorbit = false;
		gospin[0] = false;
		gospin[1] = false;
		goStretch = false;
		goSpiral = false;
		Setplayground();
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

	playground.radian.x += (playground.axis.x * 5);

	playground.radian.y += (playground.axis.y * 5);

	playground.radian.z += (playground.axis.z * 5);




	if (gospin[value] && direct) {
		glutTimerFunc(10, MyCcw, value);
	}
	else if (gospin[1 - value] && direct) {
		glutTimerFunc(10, MyCcw, 1 - value);
	}
	glutPostRedisplay();
}

GLvoid MyCw(int value) {

	playground.radian.x -= (playground.axis.x * 5);

	playground.radian.y -= (playground.axis.y * 5);

	playground.radian.z -= (playground.axis.z * 5);




	if (gospin[value] && direct == false) {
		glutTimerFunc(10, MyCw, value);
	}

	else if (gospin[1 - value] && direct == false) {
		glutTimerFunc(10, MyCw, 1 - value);
	}

	glutPostRedisplay();
}


GLvoid OrbitCcw(int value) {

	playground.Orbit += Vec3ToGLPos(playground.OrbitAxis) * 5;

	if (goorbit && playground.orbitccw) {
		glutTimerFunc(30, OrbitCcw, value);
	}
	glutPostRedisplay();
}





GLvoid OrbitCw(int value) {
	playground.Orbit -= Vec3ToGLPos(playground.OrbitAxis) * 5;


	if (goorbit && playground.orbitccw == false) {

		if (endorbit && playground.Orbit.y <= -180) {
			playground.center = playground.target;
			playground.Orbit = 0.0f;

			//glm::mat4 result = glm::mat4(1.0);

			//result *= InitRotateProj(playground[value].Orbit, { 0.0f, 0.0f, 0.0f });
			//result *= InitMoveProj(playground[value].center);
			//result *= InitScaleProj(playground[value].Stretch);

			//playground[value].center = GetProjedPos(playground[value].center, result);
			//playground[value].Orbit = 0.0f;
		}
		else
			glutTimerFunc(30, OrbitCw, value);
	}
	glutPostRedisplay();
}


