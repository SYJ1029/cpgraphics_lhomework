#pragma once


#define GLPOINT 0
#define CUBE 8

#include "VertexMethod.cpp"
#include "ProjMethod.h"

class Diagram {



public:
	int postype;
	glm::vec3 axis;
	glm::vec3 OrbitAxis;
	glm::vec3 center;
	glm::vec3 target;
	GLPos radian;
	int radcnt;
	GLPos delta;
	GLPos Stretch;
	GLPos Orbit;
	bool ccw, orbitccw;

	QuadSetting qset;


	queue<GLPos> fifo;

	Diagram() {

		postype = GLPOINT;

		radian = { 0 };
		center = glm::vec3(0.0f, 1.0f, 0.0f);
		target = glm::vec3(0.0f, 1.0f, 0.0f);
		axis = glm::vec3(0.0f, 1.0f, 0.0f);
		OrbitAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		delta = { 0, 0, 0 };

		radcnt = 1;

		for (int i = 0; i < 3; i++) {
			Stretch = { 1.0f };
		}

		ccw = true;
		orbitccw = true;



		qset.drawstyle = GLU_FILL;
		qset.normals = GLU_SMOOTH;
		qset.orientation = GLU_OUTSIDE;
	}


	void Setother_center(glm::vec3 center) {
		target = center;
	}

	float GetDist() {

		return glm::distance(center, target);
	}

	GLPos AxisToGLPos() {
		return Vec3ToGLPos(axis);
	}




	bool GetCrash(GLPos token, GLPos target) {
		GLPos prev = Vec3ToGLPos(center) + token;
		GL_Rect newtoken = Getbb(prev, Vec3ToGLPos(center));

		return (target.x >= newtoken.pos1.x && target.x <= newtoken.pos2.x) &&
			(target.y <= newtoken.pos2.y && target.y >= newtoken.pos1.y) &&
			(target.z >= newtoken.pos2.z && target.z <= newtoken.pos1.z);

	}

	void Revert() {
		delta = { 0, 0, 0 };
	}

	void Clear() {
		Revert();
		radian = { 0 };
		axis = { 0, 0, 0 };

		radcnt = 1;
	}

	void Setcol(MyObjCol col[]) {

	}

	void SetPos() {

	}

	int* AddIndexList() {

	}

	~Diagram() {
		cout << "Diagram is deleted" << endl << endl;
	}


	void SetSpin(bool ccw, glm::vec3 axis) {

		this->axis = axis;

		if (ccw)
			radcnt = 1;
		else
			radcnt = -1;
	}

	void Spin() {

	}

	void Move(GLPos delta) {
		this->delta.x += delta.x;
		this->delta.y += delta.y;
		this->delta.z += delta.z;
	}



};
