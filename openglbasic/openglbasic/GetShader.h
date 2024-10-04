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
//--- 필요한변수선언
GLint width, height;
GLuint shaderProgramID; //--- 세이더 프로그램이름
GLuint vertexShader;
GLuint fragmentShader; //--- 프래그먼트 세이더객체
GLuint VAO, VBO_position;

//--- 세이더코드저장할문자열
//--- 버텍스세이더읽어저장하고컴파일하기
//--- filetobuf: 사용자정의함수로텍스트를읽어서문자열에저장하는함수

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
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}

	
}

void make_fragmentShaders() 
{
	GLchar* fragmentSource;
	//--- 프래그먼트세이더읽어저장하고컴파일하기
	fragmentSource = filetobuf("fragment.txt");    // 프래그세이더 읽어오기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{

		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: frag_shader 컴파일 실패\n" << errorLog << std::endl;
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
		std::cerr << "ERROR: shader program 연결 실패\n" << errorLog << std::endl;
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