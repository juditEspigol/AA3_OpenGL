#include "GameObject.h"

GameObject::GameObject(GLuint _program, Transform _transform, Model _model)
	: Object(_transform), program(_program), model(_model)
{};

void GameObject::Awake()
{
	//Definir la matriz de traslacion, rotacion y escalado
	translationMatrix = MatrixUtilities::GenerateTranslationMatrix(transform.position);

	// Si la matriz de rotacion es 0 no se pintaran los modelos por lo tanto la seteamos a 1 
	if (transform.rotation == glm::vec3(0.f))
		transform.rotation = glm::vec3(1.f);

	rotationMatrix = MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation);
	
	scaleMatrix = MatrixUtilities::GenerateScaleMatrix(transform.scale);
}

void GameObject::Update() 
{

}

void GameObject::Render()
{
	//Indicar a la tarjeta GPU que programa debe usar
	glUseProgram(program);

	//Asignar valores iniciales al programa
	glUniform2f(glGetUniformLocation(program, "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);

	// Pasar las matrices
	glUniformMatrix4fv(glGetUniformLocation(program, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));
	
	if (model.HasTexture())
	{
		//Asignar valor variable de textura a usar.
		glUniform1i(glGetUniformLocation(program, "textureSampler"), model.GetTextureIndex());
	}

	model.Render(); 
}
