#include "GameObject.h"

GameObject::GameObject(GLuint _program, Transform _transform, glm::vec3 _color,
	Model _model, Texture* _texture, GLuint _renderMode)
	: Object(_transform), program(_program), color(_color), model(_model), texture(_texture), renderMode(_renderMode)
{
	// Si la matriz de rotacion es 0 no se pintaran los modelos
	if (transform.rotation == glm::vec3(0.f))
		transform.rotation = glm::vec3(1.f); 
};

void GameObject::Awake()
{
	//Definir la matriz de traslacion, rotacion y escalado
	translationMatrix = MatrixUtilities::GenerateTranslationMatrix(transform.position);
	rotationMatrix = MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.x);
		rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.y);
		rotationMatrix *= MatrixUtilities::GenerateRotationMatrix(transform.rotation, transform.rotation.z);
	scaleMatrix = MatrixUtilities::GenerateScaleMatrix(transform.scale);
}

void GameObject::Update(float _dt)
{

}

void GameObject::Render()
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

	//Vinculo su VAO para ser usado
	glBindVertexArray(model.GetVAO());

	// Dibujamos
	glDrawArrays(renderMode, 0, model.GetNumVertexs());

	//Desvinculamos VAO
	glBindVertexArray(0);
}
