#define _CRT_SECURE_NO_WARNINGS

#include "ColorStructs.h"
#include <fstream>
#include <sstream>

using namespace std;

void make_vertexShaders();
void make_fragmentShaders();
GLuint make_shaderProgram();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
//--- �ʿ��Ѻ�������
GLint width, height;
GLuint shaderProgramID; //--- ���̴� ���α׷��̸�
GLuint vertexShader;
GLuint fragmentShader; //--- �����׸�Ʈ ���̴���ü
GLuint VAO, VBO_position;

//--- ���̴��ڵ������ҹ��ڿ�
//--- ���ؽ����̴��о������ϰ��������ϱ�
//--- filetobuf: ����������Լ����ؽ�Ʈ���о���ڿ��������ϴ��Լ�

GLint result;
GLchar errorLog[512];


const float vertexPosition[] =
{
0.5, 1.0, 0.0,
0.0, 0.0, 0.0,
1.0, 0.0, 0.0
};

const float vertexColor[] =
{
1.0, 0.0, 0.0,
0.0, 1.0, 0.0,
0.0, 0.0, 1.0
};


const float vertexData[] =
{
0.5, 1.0, 0.0,			1.0, 0.0, 0.0,
0.0, 0.0, 0.0,			0.0, 1.0, 0.0,
1.0, 0.0, 0.0,			0.0, 0.0, 1.0
};

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
	GLchar* vertexSource;

	vertexSource = filetobuf("vertex.txt");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
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
	GLchar* fragmentSource;
	//--- �����׸�Ʈ���̴��о������ϰ��������ϱ�
	fragmentSource = filetobuf("fragment.txt");    // �����׼��̴� �о����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{

		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: frag_shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}

GLuint make_shaderProgram() 
{
	GLuint shaderID;
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);

	glLinkProgram(shaderID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, 512, NULL, errorLog);
		std::cerr << "ERROR: shader program ���� ����\n" << errorLog << std::endl;
		return false;
	}
	glUseProgram(shaderID);

	return shaderID;

}





GLvoid InitBuffer() {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO_position);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_position);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW);
}