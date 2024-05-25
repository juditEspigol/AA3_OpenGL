#ifndef MODEL_H
#define MODEL_H

#include <glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

class Model 
{
private:

    GLuint VAO, VBO, uvVBO, normalsVBO;
    GLuint colorVBO; 
    unsigned int numVertexs;

public:
  
    // Constructor for game objects with texture
    Model(const std::vector<float>& _vertexs, const std::vector<float>& _uvs, const std::vector<float>& _normals);
    // Constructor for primitives
    Model(const std::vector<float>& _vertexs);

    // GETTERS 
    inline GLuint GetVAO() const { return VAO; }; 
    inline GLuint GetVBO() const { return VBO; }; 
    inline GLuint GetUvVBO() const { return uvVBO; }; 
    inline unsigned int GetNumVertexs() const { return numVertexs; }; 

};

#endif
