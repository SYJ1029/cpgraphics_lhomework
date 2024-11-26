#pragma once
#include "LoadDiagramRobot.cpp"

Camera* camera;
Projection* proj;

MyCol mycolor = { 1.0f, 1.0f, 1.0f, 1.0f };
GLPos Screensize = { 800, 800, 0 };

GLUquadricObj* qobj = gluNewQuadric();
GL_Cube* cubeCw = new GL_Cube;



#define MAX_INDEX 12
#define MAX_INDEX13 2

#define PROJED true


GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid MyCw(int value);
GLvoid OrbitView(int value);
GLvoid specialKeyboard(int key, int x, int y);
GLvoid MyMove(int value);
GLvoid MoveView(int value);
GLvoid InitArmMove();
GLvoid InitLegMove();
GLvoid OpenFront(int value);
//GLvoid MyStretch(int value);



Robot* robot = new Robot;

Diagram* playground = new Diagram;


bool depthed = true;
bool gopersepective = true;
bool gospin[2] = { false, false };
bool direct = true;
bool goorbit = false;
bool endorbit = false;
bool checkPoint = false;
bool goStretch = false;
bool gomove = true;

int RedisplayID = 1;
int system_time = 20;
float speed = 0.075;


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
int mulcount = 1;


GLvoid Setplayground() {

	playground->center = { 0.0f, 0.0f, 0.0f };

	playground->radian = { 0.0f, 0.0f, 0.0f };

	playground->Stretch = { 10.0f, 10.0f, 10.0f };

	playground->Orbit = { 0.0f, 0.0f, 0.0f };

	playground->postype = ID_CUBE;
}

GLvoid InitCamera() {
	camera = new Camera(glm::vec3(20.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

GLvoid SetCamera(int id) {

	switch (id) {
	case 1:
		camera->SetCamera(glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case 2:
		camera->SetCamera(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		break;
	case 3:
		camera->SetCamera(glm::vec3(9.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	}
}

GLvoid SetProjection(int projtype) {
	delete proj;

	proj = new Projection();

	if (projtype == PROJ_ORTHO) {
		proj->InitOrtho(-1.0f, 1.0f, 1.0f, -1.0f, -15.0f, 30.0f);
	}
	else {
		proj->InitPerspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	}

	IsobjsProjed(false);
}

void DepthCheck() {
	if (depthed)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void Setindex() {
	int* p1 = cube->AddIndexList();
	int* p2 = cubeCw->AddIndexList();

	int present_bit = index_count;
	int cnt = 0;
	int begin = cnt;



	cube->start_index = 0;

	for (index_count; index_count < 36; index_count++) {
		index[index_count] = p1[index_count];

		cnt++;
	}

	//cnt += 36;

	present_bit = index_count;

	begin = cnt;

	//cnt += 12;

	cubeCw->start_index = index_count;

	present_bit = index_count;
	baseAxisIndex = index_count;

	for (index_count; index_count < present_bit + 36; index_count += 3) {
		index[index_count] = 8 + p2[index_count - begin];
		index[index_count + 1] = 8 + p2[index_count - begin + 2];
		index[index_count + 2] = 8 + p2[index_count - begin + 1];

		cnt += 3;
	}

	present_bit = index_count;

	begin = cnt;

	//cnt += 12;

	baseAxisIndex = index_count;


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_DYNAMIC_DRAW);

	free(p1);
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

	for (int i = 0; i < 8; i++) {
		mycol[i] = SetRandObjCol();
	}
	cubeCw->Setcol(mycol);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	cube->SetPos();
	cubeCw->SetPos();

	int* counter = new INT();
	(*counter) = 0;
	int type = 0;




	for (int i = 0; i < 8; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), cube->pos[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}

	for (int i = 0; i < 8; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), cubeCw->pos[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}


	Setindex();



	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);




	(*counter) = 0;


	for (int i = 0; i < 8; i++) {


		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), cube->col[i]);

		(*counter) += 3 * sizeof(GLfloat);

	}

	for (int i = 0; i < 8; i++) {


		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), cubeCw->col[i]);

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
	InitCamera();
	SetProjection(PROJ_PERSPECTIVE);
	cube->SetTranPos(200);
	cubeCw->SetTranPos(200);
	robot->InitRobot();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);


	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(specialKeyboard);
	glutMouseFunc(Mouse);


	InitArmMove();
	InitLegMove();





	glutMainLoop(); // 이벤트 처리 시작


}


GLvoid Reshape(int w, int h) { //--- 콜백 함수: 다시 그리기 콜백 함수 {

	glViewport(0, 0, w, h);

	Screensize = { (float)w, (float)h, 0.0f };
}

float radian = 10.0f;
int mycnt = 0;
glm::vec3 allAxis = glm::vec3(0.0f, 0.0f, 0.0f);

void drawScene()
{

	glClearColor(mycolor.red, mycolor.green, mycolor.blue, mycolor.alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, Screensize.x, Screensize.y);
	//SetCamera(RedisplayID);



	glUseProgram(shaderProgramID);
	glm::mat4 basemat = glm::mat4(1.0f);
	glm::mat4 rm = basemat;
	glm::mat4 rm2 = basemat;
	glm::mat4 model = basemat;
	glm::mat4 submodel = basemat;
	//glm::mat4 rm3 = glm::mat4(1.0f);

	/*model = glm::translate(model, glm::vec3(0.1f, 0.5f, 0.0f));*/
	int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform");

	glBindVertexArray(vao);




	int counter = 0;




	gluQuadricDrawStyle(qobj, playground->qset.drawstyle);
	gluQuadricNormals(qobj, playground->qset.normals);
	gluQuadricOrientation(qobj, playground->qset.orientation);



	glm::mat4 projection = glm::mat4(1.0);
	projection = proj->GetProjMatrix();
	unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);


	glm::mat4 view = glm::mat4(1.0);
	view = camera->GetViewMatix();
	unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


	model *= InitRotateProj(robot->Orbit, { 0.0f, 0.0f, 0.0f });
	model *= InitRotateProj(robot->radian, robot->body->center);
	model *= InitMoveProj(robot->center);
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));




	for (int i = ID_BODY; i <= ID_LEG2; i++) {
		counter = cube->start_index;
		submodel = model * robot->GetModelTransform(i);


		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(submodel));
		for (int j = 0; j < 6; j++) {


			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(counter * sizeof(GLfloat)));
			counter += 6;
		}
	}



	model = glm::mat4(1.0f);

	model *= InitRotateProj(playground->Orbit, { 0.0f, 0.0f, 0.0f });
	model *= InitRotateProj(playground->radian, playground->center);
	model *= InitMoveProj(playground->center);
	model *= InitScaleProj(playground->Stretch);

	counter = cubeCw->start_index;

	for (int j = 0; j < 6; j++) {
		submodel = model * cubeCw->GetWorldTransMatrix(projection, view, j);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(submodel));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(counter * sizeof(GLfloat)));
		counter += 6;
	}


	model = basemat;

	glutSwapBuffers();

}




GLvoid Mouse(int button, int state, int x, int y) {


	glutPostRedisplay();
}

GLvoid InitArmMove() {
	for (int i = 0, j = -1; i < 2; i++, j *= -1) {
		robot->arm[i]->axis = { 0.0f, 0.0f, 1.0f };



		robot->arm[i]->radcnt = j;

		if (robot->arm[i]->radcnt == robot->arm[i]->prevrad) {
			robot->arm[i]->spin = false;
			robot->arm[i]->radcnt = 0;
			break;
		}
		else {

			robot->arm[i]->prevrad = robot->arm[i]->radcnt;
		}

		if (robot->arm[i]->spin == false) {
			robot->arm[i]->spin = true;

			glutTimerFunc(10, MyCw, ID_ARM1 + i);
		}
	}


}

GLvoid InitLegMove() {

	for (int i = 0, j = 1; i < 2; i++, j *= -1) {
		robot->leg[i]->axis = { 0.0f, 0.0f, 1.0f };



		robot->leg[i]->radcnt = j;


		if (robot->leg[i]->radcnt == robot->leg[i]->prevrad && robot->leg[i]->radian.z * (float)robot->leg[i]->radcnt >= 45.0f) {
			if (i == 1)
				cout << "1" << endl;
			robot->leg[i]->spin = false;
			robot->leg[i]->radcnt = 0;
			continue;
		}
		else {
			if (i == 1)
				cout << "1" << endl;
			robot->leg[i]->prevrad = robot->leg[i]->radcnt;
		}

		if (robot->leg[i]->spin == false) {
			robot->leg[i]->spin = true;

			glutTimerFunc(10, MyCw, ID_LEG1 + i);
		}
	}
}

GLvoid Keyboard(unsigned char key, int x, int y) {

	int token = (int)key - (int)'1';
	int randnum[2];
	randnum[0] = -1, randnum[1] = -1;
	GLPos firsttoken = { 0.0f, 0.8f, 0.0f };

	switch (key) {
	case 'h':
		depthed = !(depthed);
		DepthCheck();
		break;

	case 'p':
		gopersepective = !(gopersepective);
		SetProjection(gopersepective);
		break;
	case 'o': case 'O':
		cubeCw->Delta[2] = { 0.0f, 0.0f, -1.0f };
		
		if ((int)key - (int)'a' < 0) {
			cubeCw->Delta[2].z *= -1.0f;
		}

		glutTimerFunc(system_time, OpenFront, 2);
		break;

	case 'm': case 'M':
		robot->head->axis = { 0.0f, 1.0f, 0.0f };
		if ((int)key - (int)'a' < 0) {
			if (robot->head->radcnt > 0) {
				robot->head->spin = false;
				robot->head->radcnt = 0;
				break;
			}
			robot->head->radcnt = 1;
		}
		else {
			if (robot->head->radcnt < 0) {
				robot->head->spin = false;
				robot->head->radcnt = 0;
				break;
			}
			robot->head->radcnt = -1;
		}

		if (robot->head->spin == false) {
			robot->head->spin = true;

			glutTimerFunc(10, MyCw, ID_HEAD);
		}
		break;
	case 'b': case 'B':
		if ((int)key - (int)'a' < 0) {
			robot->delta = { 0.02f, 0.0f, 0.0f };
		}
		else {
			robot->delta = { -0.02f, 0.0f, 0.0f };
		}

		if (gomove == false) {
			gomove = true;
			glutTimerFunc(10, MyMove, ID_BODY);
		}
		break;
	case 'w': case 'W':
		robot->body->delta = { -speed, 0.0f, 0.0f };

		robot->radian.y = 180;
		break;
	case 's':
		robot->body->delta = { speed, 0.0f, 0.0f };

		robot->radian.y = 0;
		break;
	case 'a': case 'A':
		robot->body->delta = { 0.0, 0.0f, speed };

		robot->radian.y = -90;
		break;
	case 'd': case 'D':
		robot->body->delta = { 0.0, 0.0f, -speed };
		robot->radian.y = 90;
		break;
	case 'R': case'r':
		break;

	case 'x': case 'X':
		if ((int)key - (int)'a' < 0 && camera->radcnt > 0 ||
			(int)key - (int)'a' >= 0 && camera->radcnt < 0) {
			camera->radcnt *= -1;
		}
		else {

		}

		if (camera->move == false) {
			camera->move = true;
			glutTimerFunc(30, MoveView, 100);
		}
		break;
	case 'y': case 'Y':
		camera->radcnt *= -1;

		if (camera->spin == false) {
			camera->spin = true;

			glutTimerFunc(30, OrbitView, 10);
		}
		break;

	case 'z': case 'Z':
		if ((int)key - (int)'a' < 0 && camera->radcnt > 0 ||
			(int)key - (int)'a' >= 0 && camera->radcnt < 0) {
			camera->radcnt *= -1;
		}
		else {

		}

		if (camera->move == false) {
			camera->move = true;
			glutTimerFunc(30, MoveView, 1);
		}
		break;


	case 'i':

		camera->Revert();
		break;
	case 'q':
		delete cube;
		delete camera;
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
		playground->center -= glm::vec3(1.0f, 0.0f, 0.0f);
		break;
	case GLUT_KEY_RIGHT:
		playground->center += glm::vec3(1.0f, 0.0f, 0.0f);
		break;
	case GLUT_KEY_UP:
		playground->center -= glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	case GLUT_KEY_DOWN:
		playground->center += glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	}

	glutPostRedisplay();
}



//GLvoid MyCcw(int value) {
//
//	.radian.x += (playground->axis.x * 5);
//
//	playground->radian.y += (playground->axis.y * 5);
//
//	playground->radian.z += (playground->axis.z * 5);
//
//
//
//
//	if (gospin[value] && direct) {
//		glutTimerFunc(10, MyCcw, value);
//	}
//	else if (gospin[1 - value] && direct) {
//		glutTimerFunc(10, MyCcw, 1 - value);
//	}
//	glutPostRedisplay();
//}

GLvoid MyCw(int value) {

	int index = value;


	switch (value) {
	case ID_HEAD:
		robot->head->radian.x += (robot->head->axis.x * 5) * (float)robot->head->radcnt;

		robot->head->radian.y += (robot->head->axis.y * 5) * (float)robot->head->radcnt;

		robot->head->radian.z += (robot->head->axis.z * 5) * (float)robot->head->radcnt;


		if (robot->head->spin)
			glutTimerFunc(30, MyCw, value);
		else {
			if (robot->head->radcnt != 0)
				robot->head->Clear();
		}
		break;
	case ID_ARM1:	case ID_ARM2:

		index -= ID_ARM1;
		robot->arm[index]->radian.x += (robot->arm[index]->axis.x * 5) * (float)robot->arm[index]->radcnt;

		robot->arm[index]->radian.y += (robot->arm[index]->axis.y * 5) * (float)robot->arm[index]->radcnt;

		robot->arm[index]->radian.z += (robot->arm[index]->axis.z * 5) * (float)robot->arm[index]->radcnt;


		if (robot->arm[index]->spin && robot->arm[index]->radian.z * (float)robot->arm[index]->radcnt <= 45.0f)
			glutTimerFunc(system_time, MyCw, value);
		else {
			if (robot->arm[index]->radian.z * robot->arm[index]->radcnt >= 45.0f)
				robot->arm[index]->radcnt *= -1;

			if (robot->arm[index]->spin == false) {
				robot->arm[index]->Clear();
				break;
			}

			glutTimerFunc(system_time, MyCw, value);
		}
		break;
	case ID_LEG1: case ID_LEG2:
		index -= ID_LEG1;

		robot->leg[index]->radian.x += (robot->leg[index]->axis.x * 5) * (float)robot->leg[index]->radcnt;

		robot->leg[index]->radian.y += (robot->leg[index]->axis.y * 5) * (float)robot->leg[index]->radcnt;

		robot->leg[index]->radian.z += (robot->leg[index]->axis.z * 5) * (float)robot->leg[index]->radcnt;


		if (robot->leg[index]->spin && robot->leg[index]->radian.z * (float)robot->leg[index]->radcnt <= 45.0f) {
			glutTimerFunc(system_time, MyCw, value);
		}
		else {
			if (robot->leg[index]->radian.z * (float)robot->leg[index]->radcnt >= 45.0f)
				robot->leg[index]->radcnt *= -1;

			if (robot->leg[index]->spin == false) {
				robot->leg[index]->Clear();
				break;
			}


			glutTimerFunc(system_time, MyCw, value);
		}
		break;
	}


	glutPostRedisplay();
}


GLvoid OrbitCcw(int value) {

	playground->Orbit += Vec3ToGLPos(playground->OrbitAxis) * 5;

	if (goorbit && playground->orbitccw) {
		glutTimerFunc(30, OrbitCcw, value);
	}
	glutPostRedisplay();
}





GLvoid OrbitView(int value) {

	camera->TimerSpinView(value);


	if (camera->spin)
		glutTimerFunc(30, OrbitView, value);
	else {
		camera->Stop();
	}

	glutPostRedisplay();
}





GLvoid MyStretchCube(int value) {
	bool TimerOn = true;

	cube->Stretch[value] += cube->StretchDelta[value];

	if ((cube->StretchDelta[value].x <= 0.0f && cube->Stretch[value].x < 0.0f) ||
		(cube->StretchDelta[value].x >= 0.0f && cube->Stretch[value].x >= 1.0f)) {
		TimerOn = false;
	}
	else;



	if (TimerOn)
		glutTimerFunc(30, MyStretchCube, value);

	glutPostRedisplay();
}


GLvoid MyMove(int value) {
	int token = value - ID_BODY;

	switch (value) {
	case ID_BODY:
		robot->Move(ID_BODY, GLPosToVec3(robot->body->delta));

		if (robot->body->center.x <= -5.0f || robot->body->center.x >= 5.0f) {
			if (robot->body->radian.x < 0) robot->body->radian.x += 180;
			if (robot->body->radian.x > 0)robot->body->radian.x -= 180;

			robot->body->delta.x *= -1;

		}

		else if (robot->body->center.z <= -5.0f || robot->body->center.z >= 5.0f) {
			if (robot->body->radian.z < 0) robot->body->radian.z += 180;
			if (robot->body->radian.z > 0)robot->body->radian.z -= 180;

			robot->body->delta.z *= -1;

		}


		break;
	case ID_ARM1: case ID_ARM2:
		robot->Move(ID_ARM1, GLPosToVec3(robot->arm[0]->delta));

		if ((robot->arm[0]->delta.z < 0 && robot->arm[0]->center.z <= -0.0f) ||
			(robot->arm[0]->delta.z > 0 && robot->arm[0]->center.z >= 0.1f)) {
			gomove = false;
		}

		break;
	}


	if (gomove) {



		glutTimerFunc(10, MyMove, value);
	}

	glutPostRedisplay();
}


GLvoid OpenFront(int value) {

	cubeCw->center[value] += cubeCw->Delta[value];

	if (cubeCw->center[value].z * cubeCw->Delta[value].z >= 200.0f) {
		robot->body->delta = { speed, 0.0f, 0.0f };
		glutTimerFunc(system_time, MyMove, ID_BODY);
	}
	else {
		glutTimerFunc(system_time / 4, OpenFront, value);
	}

	glutPostRedisplay();
}


GLvoid MoveView(int value) {
	glm::vec3 axis = { (float)(value / 100), (float)((value % 100) / 10.0f), (float)(value % 10) };
	axis /= 5.0f * camera->radcnt;


	camera->MoveViewPos(axis);

	if (camera->move)
		glutTimerFunc(30, MoveView, value);
	else {
		camera->Stop();
	}

	glutPostRedisplay();
}