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

	// Leer textura
	Texture* textureTroll = new Texture("Assets/Textures/Troll.png", GL_TEXTURE0, 0); 

	// Cargo modelo
	Model modelTroll = LoadOBJModel("Assets/Models/Troll.obj");

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

		gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
			spawnPoints[spawnPointCount],
			{ 1.f, 0.5f, 0.5f },
			modelTroll, textureTroll, GL_TRIANGLES));
	}

	gameObjects.push_back(new OrbitingObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(0.f, 0.7f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.2f)),
		{ 1.f, 1.f, 1.f },
		modelTroll, textureTroll, GL_TRIANGLES));

	gameObjects.push_back(new OrbitingObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(0.f, 0.7f, 0.f), glm::vec3(0.f, 0.f, 180.f), glm::vec3(0.2f)),
		{ 0.f, 1.f, 0.f },
		modelTroll, textureTroll, GL_TRIANGLES));
}

void ObjectManager::MoveCamera()
{
	camera->Move(GL_MANAGER.window);
}

void ObjectManager::Awake()
{
	camera->Awake();

	for (GameObject* gObj : gameObjects)
	{
		gObj->Awake();
	}
}

void ObjectManager::Update(float _dt)
{
	for (GameObject* gObj : gameObjects)
	{
		gObj->Update(_dt);
	}
}

void ObjectManager::Render()
{
	for (GameObject* gObj : gameObjects)
	{
		gObj->Render();
	}
}
