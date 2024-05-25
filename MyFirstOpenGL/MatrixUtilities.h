#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#define M_PI 3.1415926535897932384626433832795

static class MatrixUtilities
{
public:

	static glm::mat4 GenerateTranslationMatrix(glm::vec3 _translation) {

		return glm::translate(glm::mat4(1.f), _translation);
	}

	static glm::mat4 GenerateRotationMatrix(glm::vec3 _axis, float _fDegrees) {

		return glm::rotate(glm::mat4(1.f), glm::radians(_fDegrees), glm::normalize(_axis));
	}

	static glm::mat4 GenerateScaleMatrix(glm::vec3 _scaleAxis) {

		return glm::scale(glm::mat4(1.f), _scaleAxis);
	}
};