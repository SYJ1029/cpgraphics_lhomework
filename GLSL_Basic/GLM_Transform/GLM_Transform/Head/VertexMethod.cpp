#pragma once

#include "ObjStruct.h"

int index_count = 0;
int index_array_count = 0;

glm::mat4 GetMove(GLPos Delta) {
	glm::mat4 basemat = glm::mat4(1.0f);
	glm::vec3 trv = glm::vec3(Delta.x, Delta.y, Delta.z);
	glm::mat4 trm = basemat;
	glm::mat4 model = basemat;

	trm = glm::translate(basemat, trv);


	model *= trm;

	return model;
}

glm::mat4 GetSpin(GLPos Center, GLfloat radian, glm::vec3 axis) {
	glm::mat4 basemat = glm::mat4(1.0f);
	glm::mat4 trm = basemat;
	glm::mat4 rm = basemat;
	glm::mat4 model = basemat;

	glm::vec3 trv = glm::vec3(Center.x, Center.y, Center.z);

	trm = glm::translate(basemat, trv * -1.0f);
	rm = glm::rotate(basemat, glm::radians(radian), axis);
	glm::mat4 trm2 = glm::translate(basemat, trv);

	model = trm2 * rm * trm;

	return model;
}


glm::mat4 GetStretch(GLPos Stretch) {
	glm::mat4 basemat = glm::mat4(1.0f);
	glm::mat4 scm = glm::mat4(1.0f);
	glm::mat4 model = basemat;

	glm::vec3 scv = glm::vec3(Stretch.x, Stretch.y, Stretch.z);


	scm = glm::scale(basemat, scv);



	model *= scm;

	return model;
}


glm::mat4 ChangeScale(GLPos Stretch, GLPos Delta) {

	glm::mat4 model = glm::mat4(1.0f);

	model *= GetMove({ Delta.x * -1, Delta.y * -1, Delta.z * -1 });
	model *= GetStretch(Stretch);
	model *= GetMove(Delta);


	return model;
}





GLPos Vec3ToGLPos(glm::vec3 vector) {
	GLPos result = { vector.x, vector.y, vector.z };


	return result;
}

glm::vec3 GLPosToVec3(GLPos pos) {
	glm::vec3 result = { pos.x, pos.y, pos.z };


	return result;
}

GLfloat dist(GLPos a, GLPos b) {

	return glm::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) + (b.z - a.z) * (b.z - a.z));
}


GLPos GetProjedPos(GLPos pos, glm::mat4 proj) {
	glm::vec4 token = glm::vec4(GLPosToVec3(pos), 1.0f);

	token = proj * token;

	GLPos result = Vec3ToGLPos(glm::vec3(token));
	return result;
}


glm::mat4 InitMoveProj(GLPos delta) {
	glm::mat4 result = glm::mat4(1.0);

	result *= GetMove(delta);

	return result;
}


glm::mat4 InitRotateProj(GLPos radian, GLPos center) {
	glm::mat4 result = glm::mat4(1.0);

	result *= GetSpin(center, radian.x, glm::vec3(1.0f, 0.0f, 0.0f));
	result *= GetSpin(center, radian.y, glm::vec3(0.0f, 1.0f, 0.0f));
	result *= GetSpin(center, radian.z, glm::vec3(0.0f, 0.0f, 1.0f));


	return result;
}


glm::mat4 InitScaleProj(GLPos Stretch) {
	glm::mat4 result = glm::mat4(1.0);


	result *= ChangeScale(Stretch, { 0.0f, 0.0f, 0.0f });


	return result;
}






GLPos InitDelta(GLPos pos, GLPos target) {
	GLPos result = { 0 };
	GLPos line = (target - pos) / dist(pos, target);

	line = line / 50.0f;
	result += line;


	return result;
}

GL_Rect Getbb(GLPos center, GLPos target) {
	GL_Rect result = { {0}, {0} };

	if (center.x >= target.x)
		result.pos1.x = target.x, result.pos2.x = center.x;
	else
		result.pos2.x = target.x, result.pos1.x = center.x;

	if (center.y >= target.y)
		result.pos1.y = target.y, result.pos2.y = center.y;
	else
		result.pos2.y = target.y, result.pos1.y = center.y;

	if (center.z >= target.z)
		result.pos1.z = target.z, result.pos2.z = center.z;
	else
		result.pos2.z = target.z, result.pos1.z = center.z;


	return result;
}