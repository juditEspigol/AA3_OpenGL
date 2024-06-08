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

	// 2. Set GameObjects
	std::vector<glm::vec3> positionSpawns = {
		glm::vec3( 0.f,  0.f,  0.f),
		glm::vec3( 0.f,  0.f,  0.7f),
		glm::vec3( 0.f,  0.f, -0.7f),
		glm::vec3( 0.7f, 0.f,  0.f), 
		glm::vec3(-0.7f, 0.f,  0.f), 
		glm::vec3( 0.7f, 0.f,  0.7f),
		glm::vec3(-0.7f, 0.f, -0.7f),
		glm::vec3(-0.7f, 0.f,  0.7f),
		glm::vec3( 0.7f, 0.f, -0.7f)
	};
	std::vector<glm::vec3> roationSpawns = {
		glm::vec3(0.f,  90.f,  0.f), 
		glm::vec3(0.f,  180.f,  0.f), 
		glm::vec3(0.f,  270.f,  0.f), 
		glm::vec3(0.f,  0.f,  0.f)
	};
	std::set<int> keys; 
	int pos, rot;

	for (int i = 0;  i < 6; i++)
	{
		do
		{
			pos = rand() % positionSpawns.size();
			rot = rand() % roationSpawns.size();
		} 
		while (keys.find(pos) != keys.end());

		keys.insert(pos);

		if(i < 2)
			gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0], 
				Transform(positionSpawns[pos], roationSpawns[rot], glm::vec3(0.2f)), MODEL_MANAGER.models[0]));
		else if(2 < i && i < 5)
			gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0], 
				Transform(positionSpawns[pos], roationSpawns[rot], glm::vec3(0.2f)), MODEL_MANAGER.models[1]));
		else
			gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0], 
				Transform(positionSpawns[pos], roationSpawns[rot], glm::vec3(0.005f)), MODEL_MANAGER.models[2]));
	}

	// Set Orbiting objects
	gameObjects.push_back(new OrbitingObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(0.f, 0.7f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.1f)),
		MODEL_MANAGER.models[1]));
	gameObjects.push_back(new OrbitingObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(0.f, 0.7f, 0.f), glm::vec3(0.f, 0.f, 180.f), glm::vec3(0.1f)),
		MODEL_MANAGER.models[1]));

	gameObjects.push_back(new GameObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(0.f, -0.4f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(7.f, 1.f, 7.f)),
		MODEL_MANAGER.models[3]));
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
