#pragma once

#include "GetShader.cpp"
#define SIZEMAKRO 200


#define ID_CUBE 0

#define ID_BG 10
#define ID_BODY 11
#define ID_HEAD 12
#define ID_EDGE 13
#define ID_PAW 14


GL_Cube* cube = new GL_Cube;




class Crain : public Diagram {
public:
	Diagram* body;
	Diagram* head;
	Diagram* edge[2];
	Diagram* paw[2];

	glm::vec3 center;

	Crain() : Diagram() {
		body = new Diagram;
		head = new Diagram;
		edge[0] = new Diagram;
		paw[0] = new Diagram;
		edge[1] = new Diagram;
		paw[1] = new Diagram;


		body->postype = ID_CUBE;
		head->postype = ID_CUBE;

		for (int i = 0; i < 2; i++) {
			edge[i]->postype = ID_CUBE;
			head->postype = ID_CUBE;
		}
	}

	GLvoid InitCrain() {
		this->center = glm::vec3(0.0f, 0.5f, 0.0f);
		
		body->postype = ID_CUBE;
		body->center = { 0, 0.1f, 0 };
		body->Stretch = { 0.75f, 0.15f, 0.75f };

		head->postype = ID_CUBE;
		head->center = { 0, 0.1f, 0 };
		head->Stretch = { 0.5f, 0.1f, 0.5f };

		edge[0]->Stretch = {0.125f / 2, 0.75f, 0.125f / 2};

		paw[0]->center = { 0.5f, 0.0f, 0.0f };
		paw[0]->Stretch = { edge[0]->Stretch.y, edge[0]->Stretch.x, edge[0]->Stretch.z };
	}

	glm::mat4 GetModelTransform(int id) {
		glm::mat4 result = glm::mat4(1.0f);
		switch (id) {
		case ID_BODY:
			result *= InitScaleProj(body->Stretch);

			break;
		case ID_HEAD:
			result *= InitMoveProj(head->center);
			result *= InitRotateProj(head->radian, head->center);
			result *= InitScaleProj(head->Stretch);

			break;
		case ID_EDGE:
			result *= InitMoveProj(head->center);
			result *= InitScaleProj(edge[0]->Stretch);
			break;
		case ID_PAW:
			result *= InitMoveProj(paw[0]->center);
			result *= InitScaleProj(paw[0]->Stretch);
			break;
		}

		return result;
	}

	void Move(int id, glm::vec3 Delta) {
		switch (id) {
		case ID_BODY:case ID_HEAD:
			body->center += Delta;
			head->center += Delta;
			for (int i = 0; i < 2; i++) {
				edge[i]->center += Delta;
				paw[i]->center += Delta;
			}
			break;
		case ID_EDGE:
			for (int i = 0; i < 2; i++) {
				edge[i]->center += Delta;
			}
			break;
		case ID_PAW:
			for (int i = 0; i < 2; i++) {
				paw[i]->center += Delta;
			}
			break;
		}

	}

	void Spin(int id, GLPos radian) {
		switch (id) {
		case ID_BODY:case ID_HEAD:
			body->radian += radian;
			head->radian += radian;
			for (int i = 0; i < 2; i++) {
				edge[i]->radian += radian;
				paw[i]->radian += radian;
			}
			break;
		case ID_EDGE:
			for (int i = 0; i < 2; i++) {
				edge[i]->radian += radian;
			}
			break;
		case ID_PAW:
			for (int i = 0; i < 2; i++) {
				paw[i]->radian += radian;
			}
			break;
		}
	}




};


GLvoid IsobjsProjed(bool proj) {
	if (proj) {
		cube->SetTranPos(SIZEMAKRO);
	}



}



