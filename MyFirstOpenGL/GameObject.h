#pragma once
#include "Object.h"
#include "Texture.h"
#include "Model.h"

class GameObject : public Object
{
protected:

	GLuint program;

	Model model;
	glm::vec3 color; 

	GLuint renderMode;
	Texture* texture;

	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;

public:

	GameObject(GLuint _program, 
		Transform _transform, glm::vec3 _color,
		Model _model, Texture* texture, GLuint _renderMode);

	virtual void Awake() override; 
	virtual void Update(float _dt) override; 
	virtual void Render();
};
