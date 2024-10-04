#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid MyTimer(int time);

typedef struct Mycolor {
	GLclampf red;
	GLclampf green;
	GLclampf blue;
	GLclampf alpha;

}MyCol;


MyCol mycolor = { 0.0f, 0.0f, 0.0f, 1.0f };
bool timergo = false;

void main(int argc, char** argv) { //--- 윈도우 출력하고 콜백함수 설정 { //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
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
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutMainLoop(); // 이벤트 처리 시작
}



GLvoid drawScene() {
	glClearColor(mycolor.red, mycolor.green, mycolor.blue, mycolor.alpha); // 바탕색을 ‘blue’
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다


	if (timergo == true)
		glutTimerFunc(500, MyTimer, 1);
	glutSwapBuffers(); // 화면에 출력하기


}

GLvoid Reshape(int w, int h) { //--- 콜백 함수: 다시 그리기 콜백 함수 {
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y) {
	srand(time(NULL));
	float randnum = 0;

	switch (key) {
	case 'c':
		mycolor = { 0.0f, 1.0f, 1.0f, 1.0f };
		break;
	case 'm':
		mycolor = { 1.0f, 0.0f, 1.0f, 1.0f };
		break;
	case 'y':
		mycolor = { 1.0f, 1.0f, 0.0f, 1.0f };
		break;
	case 'a':
		randnum = (float)((float)rand() / RAND_MAX);
		mycolor.red = randnum;
		randnum = (float)((float)rand() / RAND_MAX);
		mycolor.green = randnum;
		randnum = (float)((float)rand() / RAND_MAX);
		mycolor.blue = randnum;

		mycolor.alpha = 1.0;
		break;
	case 'w':
		mycolor = { 1.0f, 1.0f, 1.0f, 1.0f };
		break;
	case 'k':
		mycolor = { 0.0f, 0.0f, 0.0f, 1.0f };
		break;
	case 't':
		glutTimerFunc(500, MyTimer, 0);
		timergo = true;
		break;
	case 's':
		timergo = false;
		break;
	case 'q':
		exit(EXIT_SUCCESS);
		break;
	}

	glutPostRedisplay();
}

GLvoid MyTimer(int timer) {
	float randnum = 0;
	srand(time(NULL));

	randnum = (float)((float)rand() / RAND_MAX);
	mycolor.red = randnum;
	randnum = (float)((float)rand() / RAND_MAX);
	mycolor.green = randnum;
	randnum = (float)((float)rand() / RAND_MAX);
	mycolor.blue = randnum;

	mycolor.alpha = 1.0f;

	glutPostRedisplay();
}