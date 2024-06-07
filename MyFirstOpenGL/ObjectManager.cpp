#include "ObjectManager.h"

ObjectManager::~ObjectManager()
{
	delete camera; 

	for (GameObject* gObj : gameObjects)
		delete gObj;
}

void ObjectManager::CreateObjects()
{
	// Set Camera
	camera = new Camera();

	// Cargo modelos con su pertinente textura
	std::vector<Model> models = {
		LoadOBJModel("Assets/Models/Troll.obj", new Texture("Assets/Textures/Troll.png", GL_TEXTURE0, 0), GL_TRIANGLES),
		LoadOBJModel("Assets/Models/Rock.obj", new Texture("Assets/Textures/Rock.png", GL_TEXTURE1, 1), GL_TRIANGLES),
		LoadOBJModel("Assets/Models/Fox.obj", new Texture("Assets/Textures/Fox.png", GL_TEXTURE2, 2), GL_TRIANGLES)
	};

	// 2. Set GameObjects
	std::vector<Transform> spawnPoints = {
		Transform(glm::vec3( 0.f,  0.f,  0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.2f)),
		Transform(glm::vec3( 0.f,  0.f,  0.7f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.2f)),
		Transform(glm::vec3( 0.f,  0.f, -0.7f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.2f)),
		Transform(glm::vec3( 0.7f, 0.f,  0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.2f)),
		Transform(glm::vec3(-0.7f, 0.f,  0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.2f)),
		Transform(glm::vec3( 0.7f, 0.f,  0.7f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.2f)),
		Transform(glm::vec3(-0.7f, 0.f, -0.7f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.2f)),
		Transform(glm::vec3(-0.7f, 0.f,  0.7f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.2f)),
		Transform(glm::vec3( 0.7f, 0.f, -0.7f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.2f))
	};
	std::set<int> keys; 
	int spawnPointCount;

	for (int i = 0;  i < 4; i++)
	{
		do
		{
			spawnPointCount = rand() % spawnPoints.size();
		} 
		while (keys.find(spawnPointCount) != keys.end());

		keys.insert(spawnPointCount); 

		int randomModel = rand() % 2;

		gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
			spawnPoints[spawnPointCount], models[randomModel]));
	}

	// Set Orbiting objects
	gameObjects.push_back(new OrbitingObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(0.f, 0.7f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.1f)),
		models[1]));
	gameObjects.push_back(new OrbitingObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(0.f, 0.7f, 0.f), glm::vec3(0.f, 0.f, 180.f), glm::vec3(0.1f)),
		models[1]));
}

void ObjectManager::Awake()
{
	camera->Awake();
	for (GameObject* gObj : gameObjects)
		gObj->Awake();
}

void ObjectManager::Update()
{
	camera->Update();
	camera->Inputs(GL_MANAGER.window);

	for (GameObject* gObj : gameObjects)
		gObj->Update();
}

void ObjectManager::Render()
{
	for (GameObject* gObj : gameObjects)
		gObj->Render();
}
