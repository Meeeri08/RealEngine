#include "ModuleScene.h"
/*

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Scene";
	root = new GameObject();
	root->name = "root";
	selectedGameObject = nullptr;
	inGame = false;
}

ModuleScene::~ModuleScene()
{}

*/

bool ModuleScene::SaveSettings(JsonParser* data) const
{
	bool ret = true;

	data->AddArray("GameObjects");

	//Iterate gameObjects to save them
	for (size_t i = 0; i < root->children.size(); i++)
	{
		JsonParser gameObjectData;
		root->children[i]->Save(&gameObjectData);
		data->AddArrayChild(gameObjectData);

		//Save second hierarchy of gameObjects
		for (size_t j = 0; j < root->children[i]->children.size(); j++)
		{
			root->children[i]->children[j]->Save(&gameObjectData);
			data->AddArrayChild(gameObjectData);
		}
	}
	return ret;
}