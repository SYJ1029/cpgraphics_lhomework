#pragma once

#include "Head/LoadDiagramRobot.h"



GLvoid Crain::Clear() {
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

GLvoid Crain::Revert() {
	Clear();
	InitCrain();
}

//Crain::Crain() : Diagram(){
//	Clear();
//}



GLvoid Crain::Stop() {
	this->body->spin = false;
	this->head->spin = false;

	for (int i = 0; i < 2; i++) {
		this->edge[i]->spin = false;
		this->paw[i]->spin = false;
	}
}

GLvoid Crain::InitCrain() {
	this->center = glm::vec3(0.0f, 0.5f, 0.0f);

	body->postype = ID_CUBE;
	body->center = { 0, 0.05f, 0 };
	body->Stretch = { 0.75f, 0.2f, 0.75f };

	head->postype = ID_CUBE;
	head->center = { 0, 0.1f, 0 };
	head->Stretch = { 0.5f, 0.1f, 0.5f };

	edge[0]->center = { 0.0f, 0.2f, 0.1f };
	edge[0]->Stretch = { 0.125f / 2, 0.75f, 0.125f / 2 };
	edge[1]->center = { 0.0f, 0.2f, -0.1f };
	edge[1]->Stretch = { 0.125f / 2, 0.75f, 0.125f / 2 };


	paw[0]->center = { 0.7f, 0.05f, 0.2f };
	paw[0]->Stretch = { edge[0]->Stretch.y, edge[0]->Stretch.x, edge[0]->Stretch.z };

	paw[1]->center = { 0.7f, 0.05f, -0.2f };
	paw[1]->Stretch = { edge[0]->Stretch.y, edge[0]->Stretch.x, edge[0]->Stretch.z };
}

glm::mat4 Crain::GetModelTransform(int id) {
	glm::mat4 result = glm::mat4(1.0f);

	result *= InitMoveProj(body->center);
	switch (id) {
	case ID_BODY:
		result *= InitScaleProj(body->Stretch);

		break;
	case ID_HEAD:
		result *= InitRotateProj(head->radian, head->center);
		result *= InitMoveProj(head->center);
		result *= InitRotateProj(head->radian, head->center);
		result *= InitScaleProj(head->Stretch);

		break;
	case ID_EDGE1: case ID_EDGE2:
		result *= InitRotateProj(edge[id - ID_EDGE1]->radian, edge[id - ID_EDGE1]->center);
		result *= InitMoveProj(edge[id - ID_EDGE1]->center);
		result *= InitMoveProj(head->center);
		result *= InitScaleProj(edge[id - ID_EDGE1]->Stretch);
		break;
	case ID_PAW1: case ID_PAW2:
		result *= InitRotateProj(paw[id - ID_PAW1]->radian, { paw[id - ID_PAW1]->center.x - 0.5f,  paw[id - ID_PAW1]->center.y, paw[id - ID_PAW1]->center.z });
		result *= InitMoveProj(paw[id - ID_PAW1]->center);
		result *= InitScaleProj(paw[id - ID_PAW1]->Stretch);
		break;
	}

	return result;
}

void Crain::Move(int id, glm::vec3 Delta) {
	switch (id) {
	case ID_BODY:
		body->center += Delta;
		break;
	case ID_HEAD:
		head->center += Delta;
		break;
	case ID_EDGE1: case ID_EDGE2:
		edge[0]->center += Delta;
		edge[1]->center -= Delta;

		break;
	case ID_PAW1: case ID_PAW2:
		for (int i = 0; i < 2; i++) {
			paw[i]->center += Delta;
		}
		break;
	}

}

void Crain::Spin(int id, GLPos radian) {
	switch (id) {
	case ID_BODY:case ID_HEAD:
		body->radian += radian;
		head->radian += radian;
		for (int i = 0; i < 2; i++) {
			edge[i]->radian += radian;
			paw[i]->radian += radian;
		}
		break;
	case ID_EDGE1: case ID_EDGE2:
		for (int i = 0; i < 2; i++) {
			edge[i]->radian += radian;
		}
		break;
	case ID_PAW1: case ID_PAW2:
		for (int i = 0; i < 2; i++) {
			paw[i]->radian += radian;
		}
		break;
	}
}