#define _CRT_SECURE_NO_WARNINGS

#include "ColorStructs.h"
#include <fstream>
#include <sstream>

using namespace std;

void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
//--- �ʿ��Ѻ�������
GLint width, height;
GLuint shaderProgramID; //--- ���̴� ���α׷��̸�
GLuint vertexShader;
GLuint fragmentShader; //--- �����׸�Ʈ ���̴���ü

//--- ���̴��ڵ������ҹ��ڿ�
//--- ���ؽ����̴��о������ϰ��������ϱ�
//--- filetobuf: ����������Լ����ؽ�Ʈ���о���ڿ��������ϴ��Լ�

GLint result;
GLchar errorLog[512];
GLuint vao, vbo[2];
GLchar* vertexSource;
GLchar* fragmentSource;


GLfloat triShape[3][3] = {
 { -0.5, -0.5, 0.0 }, { 0.5, -0.5, 0.0 }, { 0.0, 0.5, 0.0} };
const GLfloat colors[3][3] = {
   {  1.0,  0.0,  0.0  }, {  0.0,  1.0,  0.0  }, {  0.0,  0.0,  1.0  } };


GLchar* filetobuf(const char* vertexSource) {
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(vertexSource, "rb");
	if (!fptr)
		return NULL;
	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0;
	return buf;
}


void make_vertexShaders() {

	vertexSource = filetobuf("vertex.txt");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar**) & vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if(!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
		return;
	}

	
}

void make_fragmentShaders() 
{
	fragmentSource = filetobuf("fragment.txt");    // �����׼��̴� �о����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLint result;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{

		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: frag_shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}

void make_shaderProgram()
{

	/*make_vertexShaders();
	make_fragmentShaders();*/

	shaderProgramID = glCreateProgram();

	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgramID);

}





GLvoid InitBuffer() {

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(2, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//--- ���� colors���� ���ؽ������������Ѵ�.
	//--- colors �迭�� ������: 9 *float 
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
	//--- ������attribute �ε���1��������Ѵ�: ���ؽ���3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute �ε��� 1���� ��밡���ϰ���.
	glEnableVertexAttribArray(1);
}