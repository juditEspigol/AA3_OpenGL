#pragma once
#include "Object.h"
#include "Texture.h"
#include "Model.h"

class GameObject : public Object
{
private:

	GLuint program;

	Model model;
	glm::vec4 color; 

	GLuint renderMode;
	Texture* texture;

public:

	GameObject(GLuint _program, 
		Transform _transform, glm::vec4 _color,
		Model _model, Texture* texture, GLuint _renderMode);

 
	virtual void Update(float _dt) override; 
	virtual void Render();
};
