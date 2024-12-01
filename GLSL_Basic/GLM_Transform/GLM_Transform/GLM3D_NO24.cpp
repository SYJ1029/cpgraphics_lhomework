#pragma once
#include "Head/GetShader.cpp"

Camera* camera;
Projection* proj;

MyCol mycolor = { 1.0f, 1.0f, 1.0f, 1.0f };
GLPos Screensize = { 800, 800, 0 };

GLUquadricObj* qobj = gluNewQuadric();

GL_Cube* cube = new GL_Cube;
GL_Pyramid* pyr = new GL_Pyramid();




#define MAX_INDEX 12
#define MAX_INDEX13 2
#define PROJED true
#define ID_CUBE 0
#define ID_PYR 1


GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid MyCw(int value);
GLvoid MyCcw(int value);
GLvoid OrbitView(int value);
GLvoid specialKeyboard(int key, int x, int y);
GLvoid MyMove(int value);
GLvoid MoveView(int value);
GLvoid MyJump(int value);
//GLvoid MyStretch(int value);




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
bool onLight = true;

int RedisplayID = 1;
int system_time = 20;
float speed = 0.075;
float jumpPower = 0.3f;
float gravity = 0.05f;
float groundpoint = -4.0f;


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

	playground->Stretch = { 1.0f, 1.0f, 1.0f };

	playground->Orbit = { 0.0f, 0.0f, 0.0f };

	playground->postype = ID_CUBE;

}

GLvoid InitCamera() {
	camera = new Camera(glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
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

}

void DepthCheck() {
	if (depthed)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void Setindex() {
	int* p1 = cube->AddIndexList();
	int* p2 = pyr->AddIndexList();

	int present_bit = index_count;
	int cnt = 0;
	int begin = cnt;



	cube->start_index = 0;

	for (index_count; index_count < 36; index_count++) {
		index[index_count] = p1[index_count];

	}

	cnt += 8;

	present_bit = index_count;

	begin = present_bit;

	pyr->start_index = index_count;

	for (index_count; index_count < present_bit + 18; index_count++) {
		index[index_count] = cnt + p2[index_count - begin];

	}

	cnt += 5;


	present_bit = index_count;
	baseAxisIndex = index_count;


	begin = cnt;


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_DYNAMIC_DRAW);

	free(p1);
	free(p2);
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
	pyr->Setcol(mycol3);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	cube->SetPos();
	pyr->SetPos();

	int* counter = new INT();
	(*counter) = 0;
	int type = 0;




	for (int i = 0; i < 8; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), cube->pos[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}


	for (int i = 0; i < 5; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), pyr->pos[i]);

		(*counter) += 3 * sizeof(GLfloat);
	}


	Setindex();

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

	(*counter) = 0;

	for (int i = 0; i < 6; i++) {


		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), cube->normal[i]);

		(*counter) += 3 * sizeof(GLfloat);

	}



	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);




	(*counter) = 0;


	for (int i = 0; i < 8; i++) {


		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), cube->col[i]);

		(*counter) += 3 * sizeof(GLfloat);

	}

	for (int i = 0; i < 5; i++) {


		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), pyr->col[i]);

		(*counter) += 3 * sizeof(GLfloat);

	}




	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
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
	InitCamera();
	SetBuffer();
	Setplayground();
	SetProjection(PROJ_PERSPECTIVE);
	cube->SetTranPos(200);
	pyr->SetTranPos(200);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);


	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(specialKeyboard);
	glutMouseFunc(Mouse);





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




	glm::vec3 eye = camera->GetEYE();

	unsigned int lightPosLocation = glGetUniformLocation(shaderProgramID, "lightPos"); //--- lightPos 값 전달
	unsigned int lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor"); //--- lightColor 값 전달
	unsigned int objColorLocation = glGetUniformLocation(shaderProgramID, "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)
	unsigned int viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos"); //--- viewPos 값 전달: 카메라 위치
	unsigned int onLightLocation = glGetUniformLocation(shaderProgramID, "onLight"); //--- viewPos 값 전달: 카메라 위치


	glUniform3f(lightPosLocation, 2.0, 2.0, 2.0); // 광원의 위치

	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0); // 광원의 색


	glUniform3f(viewPosLocation, eye.x, eye.y, eye.z); // 카메라의 위치

	glUniform1i(onLightLocation, onLight);



	glm::mat4 projection = glm::mat4(1.0);
	projection = proj->GetProjMatrix();
	unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);


	glm::mat4 view = glm::mat4(1.0);
	view = camera->GetViewMatix();
	unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


	model *= glm::mat4(1.0f);
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));


	model *= InitRotateProj(playground->Orbit, { 0.0f, 0.0f, 0.0f });
	model *= InitRotateProj(playground->radian, playground->center);
	model *= InitMoveProj(playground->center);
	model *= InitScaleProj(playground->Stretch);




	switch (playground->postype) {

	case ID_CUBE:
		counter = cube->start_index;
		for (int j = 0; j < 6; j++) {
			glUniform3f(objColorLocation, 1.0, 0.5, 0.3);



			submodel = model * cube->GetWorldTransMatrix(projection, view, j);
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(submodel));

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(counter * sizeof(GLfloat)));
			counter += 6;
		}
		break;
	case ID_PYR:
		counter = pyr->start_index;
		for (int j = 0; j < 5; j++) {
			glUniform3f(objColorLocation, 1.0, 0.5, 0.3);


			submodel = model * pyr->GetWorldTransMatrix(projection, view, j);
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(submodel));

			if (j < 4) {

				glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(counter * sizeof(GLfloat)));
				counter += 3;
			}
			else {
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(counter * sizeof(GLfloat)));
				counter += 6;
			}
		}
		break;
	}




	model = glm::mat4(1.0f);



	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));





	model = basemat;

	glutSwapBuffers();

}




GLvoid Mouse(int button, int state, int x, int y) {


	glutPostRedisplay();
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
		pyr->Delta[2] = { 0.0f, 0.0f, -1.0f };

		if ((int)key - (int)'a' < 0) {
			pyr->Delta[2].z *= -1.0f;
		}

		break;
	case 'n':
		if (playground->postype == ID_CUBE)
			playground->postype = ID_PYR;
		else
			playground->postype = ID_CUBE;
		break;

	case 'm': case 'M':
		onLight = !(onLight);


		break;
	case 'b': case 'B':
		break;
	case 'w': case 'W':
		break;
	case 's':
		break;
	case 'a': case 'A':
		break;
	case 'd': case 'D':
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
		playground->radcnt = -1;

		if (playground->spin == false) {
			playground->spin = true;

			glutTimerFunc(30, MyCcw, 10);
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

	case 32:

	case 'i':

		playground->Revert();
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
	glm::vec3 prev = playground->center;
	switch (key) {
	case GLUT_KEY_LEFT:
		playground->center += glm::vec3(0.0f, 0.0f, 1.0f);
		break;
	case GLUT_KEY_RIGHT:
		playground->center -= glm::vec3(0.0f, 0.0f, 1.0f);
		break;
	case GLUT_KEY_UP:
		playground->center += glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	case GLUT_KEY_DOWN:
		playground->center -= glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	}

	glutPostRedisplay();
}



GLvoid MyCcw(int value) {

	playground->radian.x -= (playground->axis.x * 5) * playground->radcnt;

	playground->radian.y -= (playground->axis.y * 5) * playground->radcnt;

	playground->radian.z -= (playground->axis.z * 5) * playground->radcnt;


	if (playground->spin) {
		glutTimerFunc(10, MyCcw, value);
	}

	glutPostRedisplay();
}

GLvoid MyCw(int value) {

	int index = value;


	
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


int PosInRectxz(glm::vec3 pos1, int index) {

	


	return -1;
}


GLvoid MyJump(int value) {


	

	glutPostRedisplay();
}

bool CrashCheck(int value) {
	
	return false;
}

GLvoid MyMove(int value) {



	if (gomove) {



		glutTimerFunc(10, MyMove, value);
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