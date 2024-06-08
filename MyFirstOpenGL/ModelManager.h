#pragma once
#include "Model.h"

#define MODEL_MANAGER ModelManager::Instance()

class ModelManager
{
private:

	ModelManager() = default;

	ModelManager(const ModelManager&) = delete;
	ModelManager& operator =(const ModelManager&) = delete;

	Model LoadOBJModel(const std::string& _filePath, Texture* _texture, GLuint _renderMode);
	Model LoadPrimitive(const std::vector<float>& _vertexs, Texture* _texture, GLuint _renderMode);

public:

	inline static ModelManager& Instance()
	{
		static ModelManager modelManager;
		return modelManager;
	}
	~ModelManager();

	std::vector<Model> models;

	void CreateModels();
};
