#pragma once
#include "Object.h"
#include "ProgramManager.h"

class Camera : public Object
{
private:

	float fov;
	float near;
	float far;

	bool firstMouse; 
	glm::dvec2 mousePosition; 
	glm::vec2 lastMousePosition; 

	bool flashActivated; 
	bool FPressed; 

	glm::mat4 viewMatrix; 
	glm::mat4 projectionMatrix; 

	void MouseCallBack(GLFWwindow* _window, double _xPos, double _yPos);

public:

	Camera();

	virtual void Awake() override; 
	virtual void Update() override;

	void Inputs(GLFWwindow* _window);
};