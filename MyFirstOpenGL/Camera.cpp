#include "Camera.h"

Camera::Camera()
	: Object(Transform(glm::vec3(0.f, 1.7f, 4.f), glm::vec3(0.f, -90.f, 0.f))),
	fov(45.f), near(0.1f), far(10.f), front(0.f, 0.f, -1.f)
{};

void Camera::Awake()
{
	firstMouse = true; 
}

void Camera::Update(float _dt)
{
}

void Camera::Move(GLFWwindow* _window)
{
	// Detectamos inputs 
	Inputs(_window);

	// 3. Matrix generation
	glm::mat4 view = glm::lookAt(transform.position, transform.position + front, transform.up);
	glm::mat4 projection = glm::perspective(glm::radians(fov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, near, far);

	//Indicar a la tarjeta GPU que programa debe usar
	for (GLuint program : PROGRAM_MANAGER.compiledPrograms)
	{
		glUseProgram(program);

		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		
		glUniformMatrix4fv(glGetUniformLocation(program, "frontCamera"), 1, GL_FALSE, glm::value_ptr(front));
		glUniformMatrix4fv(glGetUniformLocation(program, "positionCamera"), 1, GL_FALSE, glm::value_ptr(transform.position));
	}
}

void Camera::Inputs(GLFWwindow* _window)
{
	if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS) {
		transform.position.y += 0.1f;
	}
	if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS) {
		transform.position.y -= 0.1f;
	}

	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
		transform.position.x += 0.1f;
	}
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
		transform.position.x -= 0.1f;
	}

	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
		transform.position.z += 0.1f;
	}
	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
		transform.position.z -= 0.1f;
	}

	if (glfwGetKey(_window, GLFW_KEY_PERIOD) == GLFW_PRESS) {
		fov += 1.f;
		if (fov >= 179)
			fov = 179;
	}
	if (glfwGetKey(_window, GLFW_KEY_COMMA) == GLFW_PRESS) {
		fov -= 1.f;
		if (fov < 1.f)
			fov = 1.f;
	}

	glfwGetCursorPos(_window, &mousePosition.x, &mousePosition.y);
	MouseCallBack(_window, mousePosition.x, mousePosition.y); 
}

void Camera::MouseCallBack(GLFWwindow* _window, double _xPos, double _yPos) {

	if (firstMouse) 
	{
		lastMousePosition.x = _xPos;
		lastMousePosition.y = _yPos;
		firstMouse = false; 
	}

	float xoffset = _xPos - lastMousePosition.x;
	float yoffset = lastMousePosition.y - _yPos; // Invertido porque los sistemas de coordenadas de Y van al revés
	lastMousePosition.x = _xPos;
	lastMousePosition.y = _yPos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	transform.rotation.y += xoffset;
	transform.rotation.z += yoffset;

	// Asegurarse de que pitch no pase de los límites
	if (transform.rotation.z > 89.0f)
		transform.rotation.z = 89.0f;
	if (transform.rotation.z < -89.0f)
		transform.rotation.z = -89.0f;

	front = glm::normalize(glm::vec3(
		cos(glm::radians(transform.rotation.y))* cos(glm::radians(transform.rotation.z)),
		sin(glm::radians(transform.rotation.z)),
		sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.z))
	));
}