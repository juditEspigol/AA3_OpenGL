#pragma once
#include "GameObject.h"

class OrbitingObject : public GameObject
{
private:

	float radius;

	std::vector<glm::vec3> colors = 
	{
		glm::vec3(0.0, 0.129, 0.306) , 
		glm::vec3(1.0, 0.819, 0.384) , 
		glm::vec3(0.0, 0.066, 0.266)
	}; 

public:

	OrbitingObject(GLuint _program, Transform _transform, glm::vec3 _color, Model _model, Texture* _texture, GLuint _renderMode)
		: GameObject(_program, _transform, _color, _model, _texture, _renderMode) 
	{}; 
	
	virtual void Awake() override
	{
		radius = 2; 

		//Definir la matriz de traslacion, rotacion y escalado
		translationMatrix = MatrixUtilities::GenerateTranslationMatrix(transform.position);
		rotationMatrix = MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.x);
		rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.y);
		rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.z);
		scaleMatrix = MatrixUtilities::GenerateScaleMatrix(transform.scale);
	}

	virtual void Update(float _dt) override
	{
		transform.rotation.z += 1; 
		transform.position =
		{
			radius * cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.z)),
			radius * sin(glm::radians(transform.rotation.z)),
			radius * sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.z))
		};

		//Definir la matriz de traslacion, rotacion y escalado
		translationMatrix = MatrixUtilities::GenerateTranslationMatrix(transform.position);
		rotationMatrix = MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.x);
			rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.y);
			rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.z);
		scaleMatrix = MatrixUtilities::GenerateScaleMatrix(transform.scale);
	}
	virtual void Render() override
	{
		//Indicar a la tarjeta GPU que programa debe usar
		glUseProgram(program);

		//Asignar valores iniciales al programa
		glUniform2f(glGetUniformLocation(program, "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);

		if (texture != nullptr)
		{
			//Asignar valor variable de textura a usar.
			glUniform1i(glGetUniformLocation(program, "textureSampler"), texture->textureIndex);
		}

		// Pasar las matrices
		glUniformMatrix4fv(glGetUniformLocation(program, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
		glUniformMatrix4fv(glGetUniformLocation(program, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
		glUniformMatrix4fv(glGetUniformLocation(program, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));

		InterpolationColors(); 
		glUniform3fv(glGetUniformLocation(program, "sourceLight"), 1, glm::value_ptr(transform.position));
		
		//Vinculo su VAO para ser usado
		glBindVertexArray(model.GetVAO());

		// Dibujamos
		glDrawArrays(renderMode, 0, model.GetNumVertexs());

		//Desvinculamos VAO
		glBindVertexArray(0);
	}

	void InterpolationColors()
	{
		// Normalizo el vector posicion
		glm::vec3 posNormalize = normalize(transform.position);

		// Primer cuadrante
		if (transform.position.x >= 0.f && transform.position.y > 0.f)
		{
			// valor del 0 al 1 (del 1 al 0)
			float dotProduct = posNormalize.x;
			glUniform1f(glGetUniformLocation(program, "t"), dotProduct);

			glUniform3fv(glGetUniformLocation(program, "colorA"), 1, glm::value_ptr(colors[1]));
			glUniform3fv(glGetUniformLocation(program, "colorB"), 1, glm::value_ptr(colors[2]));
		}
		// Segundo cuadrante
		if (transform.position.x < 0.f && transform.position.y > 0.f)
		{
			// valor del 0 al 1 (del 1 al 0)
			float dotProduct = posNormalize.y;
			glUniform1f(glGetUniformLocation(program, "t"), dotProduct);

			glUniform3fv(glGetUniformLocation(program, "colorA"), 1, glm::value_ptr(colors[0]));
			glUniform3fv(glGetUniformLocation(program, "colorB"), 1, glm::value_ptr(colors[1]));
		}
		// Tercer cuadrante
		if (transform.position.x < 0.f && transform.position.y <= 0.f)
		{
			// valor del 0 al 1 ( del 1 al 0)
			float dotProduct = -1 * posNormalize.x;
			glUniform1f(glGetUniformLocation(program, "t"), dotProduct);

			glUniform3fv(glGetUniformLocation(program, "colorA"), 1, glm::value_ptr(colors[2]));
			glUniform3fv(glGetUniformLocation(program, "colorB"), 1, glm::value_ptr(colors[0]));
		}
		// Cuarto cuadrante
		if (transform.position.x >= 0.f && transform.position.y <= 0.f)
		{
			// valor del 0 al 1 (del 1 al 0)
			float dotProduct = -1 * posNormalize.y;
			glUniform1f(glGetUniformLocation(program, "t"), dotProduct);

			glUniform3fv(glGetUniformLocation(program, "colorA"), 1, glm::value_ptr(colors[2]));
			glUniform3fv(glGetUniformLocation(program, "colorB"), 1, glm::value_ptr(colors[2]));
		}
	}
};