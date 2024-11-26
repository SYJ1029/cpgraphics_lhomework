#pragma once

#include "Head/LoadDiagramRobot.h"



GLvoid Robot::Clear() {
	body = new Diagram;
	head = new Diagram;
	arm[0] = new Diagram;
	leg[0] = new Diagram;
	arm[1] = new Diagram;
	leg[1] = new Diagram;


	body->postype = ID_CUBE;
	head->postype = ID_CUBE;

	for (int i = 0; i < 2; i++) {
		arm[i]->postype = ID_CUBE;
		head->postype = ID_CUBE;
		leg[i]->postype = ID_CUBE;
	}

}

GLvoid Robot::Revert() {
	Clear();
	InitRobot();
}

//Robot::Robot() : Diagram(){
//	Clear();
//}



GLvoid Robot::Stop() {
	this->body->spin = false;
	this->head->spin = false;

	for (int i = 0; i < 2; i++) {
		this->arm[i]->spin = false;
		this->leg[i]->spin = false;
	}
}

GLvoid Robot::InitRobot() {
	this->center = glm::vec3(0.0f, 0.0f, 0.0f);

	body->postype = ID_CUBE;
	body->center = { 0, -4.5f, 0 };
	body->Stretch = { 0.25f, 0.5f, 0.25f };

	head->postype = ID_CUBE;
	head->center = { 0, 0.35f, 0 };
	head->Stretch = { 0.25f, 0.25f, 0.25f };

	arm[0]->center = { 0.0f, -0.3f, 0.15f };
	arm[0]->Stretch = { 0.125f / 2, 0.4f, 0.125f / 2 };
	arm[1]->center = { 0.0f, -0.3f, -0.15f };
	arm[1]->Stretch = { 0.125f / 2, 0.4f, 0.125f / 2 };


	leg[0]->center = { 0.0f, -0.4f, 0.075f };
	leg[0]->Stretch = { 0.125f / 2, 0.4f, 0.125f / 2 };

	leg[1]->center = { 0.0f, -0.4f, -0.075f };
	leg[1]->Stretch = { 0.125f / 2, 0.4f, 0.125f / 2 };
}

glm::mat4 Robot::GetModelTransform(int id) {
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
	case ID_ARM1: case ID_ARM2:
		result *= InitRotateProj(arm[id - ID_ARM1]->radian, { arm[id - ID_ARM1]->center.x,  arm[id - ID_ARM1]->center.y + 0.5f, arm[id - ID_ARM1]->center.z });
		result *= InitMoveProj(arm[id - ID_ARM1]->center);
		result *= InitMoveProj(head->center);
		result *= InitScaleProj(arm[id - ID_ARM1]->Stretch);
		break;
	case ID_LEG1: case ID_LEG2:
		result *= InitRotateProj(leg[id - ID_LEG1]->radian, { leg[id - ID_LEG1]->center.x,  leg[id - ID_LEG1]->center.y + 0.2f, leg[id - ID_LEG1]->center.z });
		result *= InitMoveProj(leg[id - ID_LEG1]->center);
		result *= InitScaleProj(leg[id - ID_LEG1]->Stretch);
		break;
	}

	return result;
}

void Robot::Move(int id, glm::vec3 Delta) {
	switch (id) {
	case ID_BODY:
		body->center += Delta;
		break;
	case ID_HEAD:
		head->center += Delta;
		break;
	case ID_ARM1: case ID_ARM2:
		arm[0]->center += Delta;
		arm[1]->center -= Delta;

		break;
	case ID_LEG1: case ID_LEG2:
		for (int i = 0; i < 2; i++) {
			leg[i]->center += Delta;
		}
		break;
	}

}

void Robot::Spin(int id, GLPos radian) {
	switch (id) {
	case ID_BODY:case ID_HEAD:
		body->radian += radian;
		head->radian += radian;
		for (int i = 0; i < 2; i++) {
			arm[i]->radian += radian;
			leg[i]->radian += radian;
		}
		break;
	case ID_ARM1: case ID_ARM2:
		for (int i = 0; i < 2; i++) {
			arm[i]->radian += radian;
		}
		break;
	case ID_LEG1: case ID_LEG2:
		for (int i = 0; i < 2; i++) {
			leg[i]->radian += radian;
		}
		break;
	}
}



GLvoid IsobjsProjed(bool proj) {
	if (proj) {
		cube->SetTranPos(SIZEMAKRO);
	}



}