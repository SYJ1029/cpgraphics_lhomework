#pragma once
#include "ColorStructs.h"


typedef struct GLPos {
	GLfloat x;
	GLfloat y;
	GLfloat z;

	GLPos operator*(const float& num) {

		return { x * num, y * num, z * num };
	}

	GLPos operator/(const float& num) {

		return { x / num, y / num, z / num };
	}

	GLPos operator+(const GLPos& pos) {
		return { x + pos.x, y + pos.y, z + pos.z };
	}

	GLPos operator-(const GLPos& pos) {
		return { x - pos.x, y - pos.y, z - pos.z };

	}

	bool operator!=(const GLPos& pos) {

		return !((x == pos.x) && (y == pos.y) && (z == pos.z));
	}

	bool operator==(const GLPos& pos) {

		return (x == pos.x) && (y == pos.y) && (z == pos.z);
	}

	bool operator+=(const GLPos& pos) {
		x += pos.x;
		y += pos.y;
		z += pos.z;


		return true;
	}

	bool operator-=(const GLPos& pos) {
		x -= pos.x;
		y -= pos.y;
		z -= pos.z;

		return true;
	}


	bool operator*=(const GLPos& pos) {
		x *= pos.x;
		y *= pos.y;
		z *= pos.z;

		return true;
	}


	bool operator/=(const GLPos& pos) {
		x /= pos.x;
		y /= pos.y;
		z /= pos.z;

		return true;
	}

	bool operator<(const float& num) {
		return (x < num && y < num && z < num);
	}

	bool operator>(const float& num) {
		return (x > num && y > num && z > num);
	}

	bool operator<=(const float& num) {
		return (x <= num && y <= num && z <= num);
	}

	bool operator>=(const float& num) {
		return (x >= num && y >= num && z >= num);
	}

	bool operator=(const float& num) {
		x = num, y = num, z = num;

		return true;
	}


}GLPos;



typedef struct GLTexture {
	GLPos pos;
	MyObjCol col;


}GLTex;


typedef struct GL_QuadObj {
	GLint drawstyle;
	GLint normals;
	GLint orientation;

}QuadSetting;


typedef struct GL_Rect {
	GLPos pos1;
	GLPos pos2;
}GL_Rect;




GLPos Vec3ToGLPos(glm::vec3 vector) {
	GLPos result = { vector.x, vector.y, vector.z };


	return result;
}

glm::vec3 GLPosToVec3(GLPos pos) {
	glm::vec3 result = { pos.x, pos.y, pos.z };


	return result;
}
