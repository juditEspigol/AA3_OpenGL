#pragma once
#include "ModelManager.h"
#include "Camera.h"
#include "OrbitingObject.h"
#include <set>

#define OBJECT_MANAGER ObjectManager::Instance()

class ObjectManager
{
private:

	ObjectManager() = default;

	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator =(const ObjectManager&) = delete;

public:

	inline static ObjectManager& Instance()
	{
		static ObjectManager objectManager;
		return objectManager;
	}
	~ObjectManager();

	Camera* camera;
	std::vector<GameObject*> gameObjects;

	void CreateObjects();

	void Awake(); 
	void Update();
	void Render(); 
};
