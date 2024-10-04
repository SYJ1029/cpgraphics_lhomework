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
//--- 필요한변수선언
GLint width, height;
GLuint shaderProgramID; //--- 세이더 프로그램이름
GLuint vertexShader;
GLuint fragmentShader; //--- 프래그먼트 세이더객체

//--- 세이더코드저장할문자열
//--- 버텍스세이더읽어저장하고컴파일하기
//--- filetobuf: 사용자정의함수로텍스트를읽어서문자열에저장하는함수

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
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}

	
}

void make_fragmentShaders() 
{
	fragmentSource = filetobuf("fragment.txt");    // 프래그세이더 읽어오기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLint result;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{

		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: frag_shader 컴파일 실패\n" << errorLog << std::endl;
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
	//--- 변수 colors에서 버텍스색상을복사한다.
	//--- colors 배열의 사이즈: 9 *float 
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
	//--- 색상값을attribute 인덱스1번에명시한다: 버텍스당3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 1번을 사용가능하게함.
	glEnableVertexAttribArray(1);
}