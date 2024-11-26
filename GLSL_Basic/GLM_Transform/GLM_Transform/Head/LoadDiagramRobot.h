#pragma once

#include "GetShader.cpp"
#define SIZEMAKRO 200


#define ID_CUBE 0

#define ID_BG 10
#define ID_BODY 11
#define ID_HEAD 12
#define ID_ARM1 13
#define ID_ARM2 14
#define ID_LEG1 15
#define ID_LEG2 16



GL_Cube* cube = new GL_Cube;




class Crain : public Diagram {
public:
	Diagram* body;
	Diagram* head;
	Diagram* edge[2];
	Diagram* paw[2];

	glm::vec3 center;



	Crain() : Diagram() {
		Clear();
	}

	GLvoid Clear();

	GLvoid Revert();

	GLvoid Stop();

	GLvoid InitCrain();

	glm::mat4 GetModelTransform(int id);

	void Move(int id, glm::vec3 Delta);

	void Spin(int id, GLPos radian);




};


GLvoid IsobjsProjed(bool proj) {
	if (proj) {
		cube->SetTranPos(SIZEMAKRO);
	}



}




class Robot : public Diagram {
public:
	Diagram* body;
	Diagram* head;
	Diagram* arm[2];
	Diagram* leg[2];

	glm::vec3 center;

	Robot() : Diagram() {
		Clear();
	}

	GLvoid Clear();

	GLvoid Revert();

	GLvoid Stop();

	GLvoid InitRobot();

	glm::mat4 GetModelTransform(int id);

	void Move(int id, glm::vec3 Delta);

	void Spin(int id, GLPos radian);
};