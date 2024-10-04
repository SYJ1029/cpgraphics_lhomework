#include <iostream>
#include <gl/glew.h> //--- �ʿ��� ������� include
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

void main(int argc, char** argv) { //--- ������ ����ϰ� �ݹ��Լ� ���� { //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(0, 0); // �������� ��ġ ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
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
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutMainLoop(); // �̺�Ʈ ó�� ����
}



GLvoid drawScene() {
	glClearColor(mycolor.red, mycolor.green, mycolor.blue, mycolor.alpha); // �������� ��blue��
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�


	if (timergo == true)
		glutTimerFunc(500, MyTimer, 1);
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�


}

GLvoid Reshape(int w, int h) { //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� {
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