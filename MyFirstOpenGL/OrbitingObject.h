#pragma once
#include "GameObject.h"

class OrbitingObject : public GameObject
{
private:

	float orbitRadius;
	std::vector<glm::vec3> colors;

	float interpolationValue; 
	glm::vec3 colorA; 
	glm::vec3 colorB; 

	void InterpolationColor();

public:

	OrbitingObject(GLuint _program, Transform _transform, Model _model, float _orbitRadius = 2.f);

	virtual void Update() override;
};