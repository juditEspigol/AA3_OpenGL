#pragma once
#include "Object.h"
#include "Texture.h"
#include "Model.h"

class GameObject : public Object
{
protected:

	GLuint program;

	Model model;

	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;

public:

	GameObject(GLuint _program, Transform _transform, Model _model);

	virtual void Awake() override; 
	virtual void Update() override; 

	virtual void Render();
};
