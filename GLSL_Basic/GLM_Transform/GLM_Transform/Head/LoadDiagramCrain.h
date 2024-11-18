#pragma once

#include "GetShader.h"
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

	void Move(int id, GLPos Delta) {
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



