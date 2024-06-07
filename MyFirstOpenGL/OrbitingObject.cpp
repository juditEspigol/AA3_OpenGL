#include "OrbitingObject.h"

OrbitingObject::OrbitingObject(GLuint _program, Transform _transform, Model _model, float _orbitRadius)
	: GameObject(_program, _transform, _model), orbitRadius(_orbitRadius)
{
	colors = { glm::vec3(0.0, 0.129, 0.306), glm::vec3(1.0, 0.819, 0.384), glm::vec3(0.0, 0.066, 0.266) };
};

void OrbitingObject::Update()
{
	// Update movimiento
	transform.rotation.z += 0.5;
	transform.position =
	{
		orbitRadius * cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.z)),
		orbitRadius * sin(glm::radians(transform.rotation.z)),
		orbitRadius * sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.z))
	};

	//Definir la matriz de traslacion, rotacion y escalado
	translationMatrix = MatrixUtilities::GenerateTranslationMatrix(transform.position);
	rotationMatrix = MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation);
	scaleMatrix = MatrixUtilities::GenerateScaleMatrix(transform.scale);

	// Set spot light at position
	glUniform3fv(glGetUniformLocation(program, "sourceLight"), 1, glm::value_ptr(transform.position));

	// Seteamos de ambient color range
	InterpolationColor();
	glUniform1f(glGetUniformLocation(program, "t"), interpolationValue);
	glUniform3fv(glGetUniformLocation(program, "colorA"), 1, glm::value_ptr(colorA));
	glUniform3fv(glGetUniformLocation(program, "colorB"), 1, glm::value_ptr(colorB));
}

void OrbitingObject::InterpolationColor()
{
	// Normalizo el vector posicion
	glm::vec3 posNormalize = normalize(transform.position);

	// Primer cuadrante
	if (transform.position.x >= 0.f && transform.position.y > 0.f)
	{
		// valor del 0 al 1 (del 1 al 0)
		interpolationValue = posNormalize.x;
		colorA = colors[1];
		colorB = colors[2];
	}
	// Segundo cuadrante
	if (transform.position.x < 0.f && transform.position.y > 0.f)
	{
		// valor del 0 al 1 (del 1 al 0)
		interpolationValue = posNormalize.y;
		colorA = colors[0];
		colorB = colors[1];
	}
	// Tercer cuadrante
	if (transform.position.x < 0.f && transform.position.y <= 0.f)
	{
		// valor del 0 al 1 ( del 1 al 0)
		interpolationValue = -1 * posNormalize.x;
		colorA = colors[2];
		colorB = colors[0];
	}
	// Cuarto cuadrante
	if (transform.position.x >= 0.f && transform.position.y <= 0.f)
	{
		// valor del 0 al 1 (del 1 al 0)
		interpolationValue = -1 * posNormalize.y;
		colorA = colors[2];
		colorB = colors[2];
	}
}