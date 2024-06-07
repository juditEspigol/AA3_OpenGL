#ifndef MODEL_H
#define MODEL_H

#include <glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Texture.h"

class Model 
{
private:

    GLuint VAO, VBO, uvVBO, normalsVBO;
    GLuint colorVBO; 
    unsigned int numVertexs;

    Texture* texture; 
    GLuint renderMode; 

public:

    // Constructor for game objects with texture
    Model(const std::vector<float>& _vertexs, const std::vector<float>& _uvs, const std::vector<float>& _normals, Texture* _texture, GLuint _renderMode);
    // Constructor for primitives
    Model(const std::vector<float>& _vertexs, Texture* _texture, GLuint _renderMode);

    void Render(); 

    inline bool HasTexture() const { return texture == nullptr? false : true; }; 
    inline int GetTextureIndex() const { return texture->textureIndex; }; 

};

Model LoadOBJModel(const std::string& _filePath, Texture* _texture, GLuint _renderMode);
Model LoadPrimitive(const std::vector<float>& _vertexs, Texture* _texture, GLuint _renderMode);

#endif
