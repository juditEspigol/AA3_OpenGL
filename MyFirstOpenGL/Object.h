#pragma once
#include <glm.hpp>
#include <vector>
#include <GL/glew.h>
#include <gtc/type_ptr.hpp>
#include <stb_image.h>

#include "GLManager.h"
#include "Transform.h"
#include "MatrixUtilities.h"

class Object
{
protected:
	
	Transform transform; 

public:

	Object(Transform _transform)
		:transform(_transform)
	{};

	virtual void Awake() = 0;
	virtual void Update() = 0;
};

