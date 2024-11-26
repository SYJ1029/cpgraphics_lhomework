#pragma once
#include "LoadDiagramRobot.cpp"

Camera* camera;
Projection* proj;

MyCol mycolor = { 1.0f, 1.0f, 1.0f, 1.0f };
GLPos Screensize = { 800, 800, 0 };

GLUquadricObj* qobj = gluNewQuadric();




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
//GLvoid MyStretch(int value);



Crain* crain = new Crain;

Diagram playground;


bool depthed = true;
bool gopersepective = true;
bool gospin[2] = { false, false };
bool direct = true;
bool goorbit = false;
bool endorbit = false;
bool checkPoint = false;
bool goStretch = false;
bool gomove = false;

int RedisplayID = 1;


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

	playground.center = { 0.0f, 0.0f, 0.0f };

	playground.radian = { 0.0f, 0.0f, 0.0f };

	playground.Stretch = { 0.2f, 0.2f, 0.2f };

	playground.Orbit = { 0.0f, 0.0f, 0.0f };

	playground.postype = ID_CUBE;
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

	cout << sizeof((p1));

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


	present_bit = index_count;
	baseAxisIndex = index_count;

	for (index_count; index_count < present_bit + 6; index_count++, index_array_count++) {
		index[index_count] = 8 + index_array_count;
	}



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

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, (MAX_INDEX * 10000) * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	cube->SetPos();

	//float* counter = new FLOAT();
	int* counter = new INT();
	(*counter) = 0;
	int type = 0;




	for (int i = 0; i < 8; i++) {
		glBufferSubData(GL_ARRAY_BUFFER, (*counter),
			3 * sizeof(GLfloat), cube->pos[i]);

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
	InitCamera();
	SetProjection(PROJ_PERSPECTIVE);
	cube->SetTranPos(200);
	crain->InitCrain();
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

	for (RedisplayID = 1; RedisplayID <= 3; RedisplayID++) {
		switch (RedisplayID) {
		case 1:
			glViewport(0, 0, Screensize.x, Screensize.y);
			SetProjection(PROJ_PERSPECTIVE);
			break;
		case 2:
			glViewport(0, 0, Screensize.x / 4, Screensize.y / 4);
			SetProjection(PROJ_ORTHO);
			break;
		case 3:
			glViewport(Screensize.x / 4 * 2, 0, Screensize.x, Screensize.y / 4);
			SetProjection(PROJ_ORTHO);
			break;
		}

		SetCamera(RedisplayID);


		//gluLookAt(0.0, 0.0, 100.0f, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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




		gluQuadricDrawStyle(qobj, playground.qset.drawstyle);
		gluQuadricNormals(qobj, playground.qset.normals);
		gluQuadricOrientation(qobj, playground.qset.orientation);



		glm::mat4 projection = glm::mat4(1.0);
		projection = proj->GetProjMatrix();
		unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projectionTransform");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);


		glm::mat4 view = glm::mat4(1.0);
		view = camera->GetViewMatix();
		unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


		model *= InitRotateProj(crain->Orbit, { 0.0f, 0.0f, 0.0f });
		model *= InitRotateProj(crain->radian, crain->center);
		model *= InitMoveProj(crain->center);
		//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));




		for (int i = ID_BODY; i <= ID_PAW2; i++) {
			counter = cube->start_index;
			submodel = model * crain->GetModelTransform(i);
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(submodel));
			for (int j = 0; j < 6; j++) {


				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(counter * sizeof(GLfloat)));
				counter += 6;
			}
		}






		model = basemat;








		model = basemat;


		model = rm2 * rm;

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, (void*)(baseAxisIndex * sizeof(GLfloat)));
		counter += 6 * sizeof(GLint);




	}
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

	case 'e': case 'E':


		if (direct) {
			for (int i = 0, j = 1; i < 2; i++, j *= -1) {
				crain->edge[i]->radcnt = j;
				crain->edge[i]->delta = { 0.0f, 0.0f, -0.01f };
				crain->edge[i]->delta = crain->edge[i]->delta * crain->edge[i]->radcnt;
			}
		}
		else {
			for (int i = 0, j = 1; i < 2; i++, j *= -1) {
				crain->edge[i]->radcnt = j;
				crain->edge[i]->delta = { 0.0f, 0.0f, 0.01f };
				crain->edge[i]->delta = crain->edge[i]->delta * crain->edge[i]->radcnt;
			}
		}

		direct = !(direct);
		gomove = true;
		glutTimerFunc(30, MyMove, ID_EDGE1);
		break;
	case 'f': case 'F':
		for (int i = 0, j = 1; i < 2; i++, j *= -1) {
			crain->paw[i]->axis = { 0.0f, 0.0f, 1.0f };



			if ((int)key - (int)'a' < 0) {

				crain->paw[i]->radcnt = j;
			}
			else {
				crain->paw[i]->radcnt = j * -1;
			}

			if (crain->paw[i]->radcnt == crain->paw[i]->prevrad && crain->paw[i]->radian.z * (float)crain->paw[i]->radcnt >= 45.0f) {
				if (i == 1)
					cout << "1" << endl;
				crain->paw[i]->spin = false;
				crain->paw[i]->radcnt = 0;
				continue;
			}
			else {
				if (i == 1)
					cout << "1" << endl;
				crain->paw[i]->prevrad = crain->paw[i]->radcnt;
			}

			if (crain->paw[i]->spin == false) {
				crain->paw[i]->spin = true;

				glutTimerFunc(10, MyCw, ID_PAW1 + i);
			}
		}


		break;
	case 't': case 'T':
		for (int i = 0, j = 1; i < 2; i++, j *= -1) {
			crain->edge[i]->axis = { 0.0f, 1.0f, 0.0f };



			if ((int)key - (int)'a' < 0) {

				crain->edge[i]->radcnt = j;
			}
			else {
				crain->edge[i]->radcnt = j * -1;
			}

			if (crain->edge[i]->radcnt == crain->edge[i]->prevrad) {
				crain->edge[i]->spin = false;
				crain->edge[i]->radcnt = 0;
				break;
			}
			else {

				crain->edge[i]->prevrad = crain->edge[i]->radcnt;
			}

			if (crain->edge[i]->spin == false) {
				crain->edge[i]->spin = true;

				glutTimerFunc(10, MyCw, ID_EDGE1 + i);
			}
		}


		break;

	case 'm': case 'M':
		crain->head->axis = { 0.0f, 1.0f, 0.0f };
		if ((int)key - (int)'a' < 0) {
			if (crain->head->radcnt > 0) {
				crain->head->spin = false;
				crain->head->radcnt = 0;
				break;
			}
			crain->head->radcnt = 1;
		}
		else {
			if (crain->head->radcnt < 0) {
				crain->head->spin = false;
				crain->head->radcnt = 0;
				break;
			}
			crain->head->radcnt = -1;
		}

		if (crain->head->spin == false) {
			crain->head->spin = true;

			glutTimerFunc(10, MyCw, ID_HEAD);
		}
		break;
	case 'b': case 'B':
		if ((int)key - (int)'a' < 0) {
			crain->delta = { 0.02f, 0.0f, 0.0f };
		}
		else {
			crain->delta = { -0.02f, 0.0f, 0.0f };
		}

		if (gomove == false) {
			gomove = true;
			glutTimerFunc(10, MyMove, ID_BODY);
		}
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

	case 'o':
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

	case 's':
		gomove = false;

		crain->Stop();
		camera->Stop();
		break;
	case 'c':
		gomove = false;

		crain->Revert();
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
		playground.center -= glm::vec3(1.0f, 0.0f, 0.0f);
		break;
	case GLUT_KEY_RIGHT:
		playground.center += glm::vec3(1.0f, 0.0f, 0.0f);
		break;
	case GLUT_KEY_UP:
		playground.center -= glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	case GLUT_KEY_DOWN:
		playground.center += glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	}

	glutPostRedisplay();
}



//GLvoid MyCcw(int value) {
//
//	.radian.x += (playground.axis.x * 5);
//
//	playground.radian.y += (playground.axis.y * 5);
//
//	playground.radian.z += (playground.axis.z * 5);
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

	switch (value) {
	case ID_HEAD:
		crain->head->radian.x += (crain->head->axis.x * 5) * (float)crain->head->radcnt;

		crain->head->radian.y += (crain->head->axis.y * 5) * (float)crain->head->radcnt;

		crain->head->radian.z += (crain->head->axis.z * 5) * (float)crain->head->radcnt;


		if (crain->head->spin)
			glutTimerFunc(30, MyCw, value);
		else {
			if (crain->head->radcnt != 0)
				crain->head->Clear();
		}
		break;
	case ID_EDGE1:
		crain->edge[0]->radian.x += (crain->edge[0]->axis.x * 5) * (float)crain->edge[0]->radcnt;

		crain->edge[0]->radian.y += (crain->edge[0]->axis.y * 5) * (float)crain->edge[0]->radcnt;

		crain->edge[0]->radian.z += (crain->edge[0]->axis.z * 5) * (float)crain->edge[0]->radcnt;


		if (crain->edge[0]->spin)
			glutTimerFunc(30, MyCw, value);
		else {
			if (crain->edge[0]->radcnt != 0)
				crain->edge[0]->Clear();
		}
		break;
	case ID_EDGE2:
		crain->edge[1]->radian.x += (crain->edge[1]->axis.x * 5) * (float)crain->edge[1]->radcnt;

		crain->edge[1]->radian.y += (crain->edge[1]->axis.y * 5) * (float)crain->edge[1]->radcnt;

		crain->edge[1]->radian.z += (crain->edge[1]->axis.z * 5) * (float)crain->edge[1]->radcnt;


		if (crain->edge[1]->spin)
			glutTimerFunc(30, MyCw, value);
		else {
			if (crain->edge[1]->radcnt != 0)
				crain->edge[1]->Clear();
		}
		break;
	case ID_PAW1:
		crain->paw[0]->radian.x += (crain->paw[0]->axis.x * 5) * (float)crain->paw[0]->radcnt;

		crain->paw[0]->radian.y += (crain->paw[0]->axis.y * 5) * (float)crain->paw[0]->radcnt;

		crain->paw[0]->radian.z += (crain->paw[0]->axis.z * 5) * (float)crain->paw[0]->radcnt;


		if (crain->paw[0]->spin && crain->paw[0]->radian.z * (float)crain->paw[0]->radcnt <= 45.0f) {
			glutTimerFunc(30, MyCw, value);
		}
		else {
			if (crain->paw[0]->radian.z * (float)crain->paw[0]->radcnt >= 45.0f)
				crain->paw[0]->radcnt = 0;

			if (crain->paw[0]->radcnt != 0)
				crain->paw[0]->Clear();


			crain->paw[value - ID_PAW1]->spin = false;
			crain->paw[value - ID_PAW1]->radcnt = 0;
		}
		break;
	case ID_PAW2:
		crain->paw[1]->radian.x += (crain->paw[1]->axis.x * 5) * (float)crain->paw[1]->radcnt;

		crain->paw[1]->radian.y += (crain->paw[1]->axis.y * 5) * (float)crain->paw[1]->radcnt;

		crain->paw[1]->radian.z += (crain->paw[1]->axis.z * 5) * (float)crain->paw[1]->radcnt;


		if (crain->paw[1]->spin && crain->paw[1]->radian.z * (float)crain->paw[1]->radcnt <= 45.0f)
			glutTimerFunc(30, MyCw, value);
		else {
			if (crain->paw[1]->radian.z * (float)crain->paw[1]->radcnt >= 45.0f)
				crain->paw[1]->radcnt = 0;

			if (crain->paw[1]->radcnt != 0)
				crain->paw[1]->Clear();

			crain->paw[value - ID_PAW1]->spin = false;
			crain->paw[value - ID_PAW1]->radcnt = 0;
		}
		break;
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





GLvoid OrbitView(int value) {

	camera->TimerSpinView(value);


	if (camera->spin)
		glutTimerFunc(30, OrbitView, value);
	else {
		camera->Stop();
	}

	glutPostRedisplay();
}



//GLvoid MyLineMoveCube(int value) {
//	GLPos token = { 0 };
//
//
//	//cube->center[value] += {0.0f, 2.0f, 0.0f};
//
//
//
//	if (cube->fifo[value].empty());
//	else {
//		token = cube->fifo[value].front();
//		cube->center[value] += InitDelta(cube->center[value], token) * cube->mulcount;
//	}
//
//	if (cube->GetCrash(InitDelta(cube->center[value], token) * cube->mulcount, token, value) == false) {
//		glutTimerFunc(10, MyLineMoveCube, value);
//	}
//
//	else {
//		cube->center[value] = token;
//
//		cube->fifo[value].pop();
//
//		if (cube->fifo[value].empty()) {
//			cout << "empty!" << endl << endl;
//		}
//		else {
//			glutTimerFunc(30, MyLineMoveCube, value);
//		}
//
//
//	}
//
//	glutPostRedisplay();
//}



GLvoid MyStretchCube(int value) {
	bool TimerOn = true;

	cube->Stretch[value] += cube->StretchDelta[value];

	if ((cube->StretchDelta[value].x <= 0.0f && cube->Stretch[value].x < 0.0f) ||
		(cube->StretchDelta[value].x >= 0.0f && cube->Stretch[value].x >= 1.0f)) {
		TimerOn = false;
	}
	else;

	//if (cube->StretchDelta[value].x >= 0.0f && cube->Stretch[value].x >= 1.0f) {
	//	TimerOn = false;
	//}
	//else;


	if (TimerOn)
		glutTimerFunc(30, MyStretchCube, value);

	glutPostRedisplay();
}


GLvoid MyMove(int value) {
	int token = value - ID_BODY;

	switch (value) {
	case ID_BODY:
		crain->Move(ID_BODY, GLPosToVec3(crain->delta));
		break;
	case ID_EDGE1: case ID_EDGE2:
		crain->Move(ID_EDGE1, GLPosToVec3(crain->edge[0]->delta));

		if ((crain->edge[0]->delta.z < 0 && crain->edge[0]->center.z <= -0.0f) ||
			(crain->edge[0]->delta.z > 0 && crain->edge[0]->center.z >= 0.1f)) {
			gomove = false;
		}

		break;
	}


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