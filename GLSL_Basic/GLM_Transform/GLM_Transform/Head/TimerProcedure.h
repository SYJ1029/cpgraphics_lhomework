#pragma once

#include "VertexMethod.h"



GLPos InitDelta(GLPos pos, GLPos target) {
	GLPos result = { 0 };
	GLPos line = (target - pos) / dist(pos, target);

	line = line / 50.0f;
	result += line;


	return result;
}