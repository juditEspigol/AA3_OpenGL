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

	// Leer texturas
	std::vector<Texture*> textures = {
		new Texture("Assets/Textures/Troll.png", GL_TEXTURE0, 0), 
		new Texture("Assets/Textures/Rock.png", GL_TEXTURE1, 1),
		new Texture("Assets/Textures/Fox.png", GL_TEXTURE2, 2)
	};

	// Cargo modelos
	std::vector<Model> models = {
		LoadOBJModel("Assets/Models/Troll.obj"),
		LoadOBJModel("Assets/Models/Rock.obj"),
		LoadOBJModel("Assets/Models/Fox.obj")
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
			spawnPoints[spawnPointCount],
			{ 1.f, 0.5f, 0.5f },
			models[randomModel], textures[randomModel], GL_TRIANGLES));
	}


	gameObjects.push_back(new OrbitingObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(0.f, 0.7f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.005f)),
		{ 1.f, 1.f, 1.f },
		models[2], textures[2], GL_TRIANGLES));

	gameObjects.push_back(new OrbitingObject(PROGRAM_MANAGER.compiledPrograms[0],
		Transform(glm::vec3(0.f, 0.7f, 0.f), glm::vec3(0.f, 0.f, 180.f), glm::vec3(0.005f)),
		{ 0.f, 1.f, 0.f },
		models[2], textures[2], GL_TRIANGLES));
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
