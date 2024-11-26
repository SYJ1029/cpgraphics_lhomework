#pragma once

#include "GetShader.cpp"
#define SIZEMAKRO 200


#define ID_CUBE 0

#define ID_BG 10
#define ID_BODY 11
#define ID_HEAD 12
#define ID_EDGE1 13
#define ID_EDGE2 14
#define ID_PAW1 15
#define ID_PAW2 16



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