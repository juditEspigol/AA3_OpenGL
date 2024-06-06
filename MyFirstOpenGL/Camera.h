#pragma once
#include "Object.h"
#include "ProgramManager.h"

class Camera : public Object
{
private:

	glm::vec3 front; 

	float fov;
	float near;
	float far;

	bool firstMouse; 
	glm::dvec2 mousePosition; 
	glm::vec2 lastMousePosition; 


public:

	Camera();

	virtual void Awake() override; 
	virtual void Update(float _dt) override;

	void Move(GLFWwindow* _window);

	void Inputs(GLFWwindow* _window);
	void MouseCallBack(GLFWwindow* _window, double _xPos, double _yPos);
};