#pragma once

#include "../BaseHeader.h"


class Camera {
private:
	glm::vec3 EYE;
	glm::vec3 AT;
	glm::vec3 UP;
	glm::vec3 InitEYE;

	
public:
	glm::vec3 radian;
	int radcnt;
	bool spin;
	bool move;

	void Clear() {
		this->EYE = glm::vec3(0.0f);
		this->AT = glm::vec3(0.0f);
		this->UP = glm::vec3(0.0f);
		this->InitEYE = glm::vec3(0.0f);

		this->radian = { 0.0f, 0.0f, 0.0f };
		this->radcnt = 5;
		this->spin = false;
		this->move = false;
	}

	Camera() {
		Clear();
	}

	Camera(glm::vec3 EYE, glm::vec3 AT, glm::vec3 UP) : Camera(){
		this->EYE = EYE;
		this->AT = AT;
		this->UP = UP;
		this->InitEYE = EYE;
	}

	void SetCamera(glm::vec3 EYE, glm::vec3 AT, glm::vec3 UP) {
		this->EYE = EYE;
		this->AT = AT;
		this->UP = UP;
		this->InitEYE = EYE;
	}

	void Stop() {
		this->spin = false;
		this->move = false;
	}

	void Revert() {
		this->radian = { 0.0f, 0.0f, 0.0f };
		this->radcnt = 5;
		this->EYE = this->InitEYE;

		Stop();
	}




	glm::mat4 GetViewMatix() {
		glm::mat4 view = glm::lookAt(EYE, AT, UP);

		return view;
	}

	void MoveViewPos(glm::vec3 EYE) {
		this->EYE += EYE;
	}

	void MoveViewDirect(glm::vec3 AT) {
		this->AT += AT;
	}

	void MoveUpVector(glm::vec3 UP) {
		this->UP += UP;
	}

	GLvoid TimerSpinView(int value) {
		glm::vec3 axis = { (float)(value / 100), (float)((value % 100) / 10.0f), (float)(value % 10) };
		glm::mat4 spinmat = glm::mat4(1.0f);


		this->radian.x += (float)this->radcnt * axis.x;
		this->radian.y += (float)this->radcnt * axis.y;		
		this->radian.z += (float)this->radcnt * axis.z;



		spinmat = InitRotateProj(Vec3ToGLPos(this->radian), this->AT);

		if (this->radian.y <= -1000.0f)
			cout << this->radian.x << ", " << this->radian.z << endl;

		this->EYE = glm::vec3(spinmat * glm::vec4(this->InitEYE, 1.0f));

	}

};

