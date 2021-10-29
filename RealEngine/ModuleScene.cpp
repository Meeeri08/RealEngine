#include "ModuleScene.h"


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

bool ModuleScene::Start()
{
	bool ret = true;
	ImGuizmo::Enable(false);
	return ret;
}

update_status ModuleScene::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleScene::Update(float dt)
{
	if (selected_GO != nullptr)
	{
		if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_IDLE)
		{
			if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT)
			{
				guizmoOperation = ImGuizmo::NO_OPERATION;
			}
			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			{
				guizmoOperation = ImGuizmo::TRANSLATE;
			}
			if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT)
			{
				guizmoOperation = ImGuizmo::ROTATE;
			}
			if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT)
			{
				guizmoOperation = ImGuizmo::SCALE;
			}
		}
	}

	return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate(float dt)
{
	DrawGameObjects(GetRoot(), GetRoot());
	UpdateGameObjects(GetRoot());
	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	bool ret = true;
	delete root;
	return ret;
}

GameObject* ModuleScene::CreateGameObject(std::string name, float3 position, Quat rotation, float3 scale, GameObject* parent, char* mesh_path, char* texture_path)
{
	GameObject* newGameObject = nullptr;
	newGameObject = new GameObject();
	newGameObject->ChangeName(name);

	if (newGameObject != nullptr)
		AddChild(newGameObject, parent);

	//newGameObject->transform->SetPosition(position);
	//newGameObject->transform->SetQuaternionRotation(rotation);
	//newGameObject->transform->SetScale(scale);
	//newGameObject->transform->changed = true;

	return newGameObject;
}

void ModuleScene::DestroyGameObject(GameObject* selectedGameObject)
{
	selectedGameObject->components.clear();

	for (int i = 0; i < root->children.size(); i++)
	{
		if (root->children[i]->children.empty() == false)
		{
			for (size_t j = 0; j < root->children[i]->children.size(); j++)
			{
				if (root->children[i]->children[j] == selectedGameObject)
				{
					root->children[i]->children.erase(root->children[i]->children.begin() + j);
				}
			}
		}
		if (root->children[i] == selectedGameObject)
		{
			root->children.erase(root->children.begin() + i);
		}
	}

	if (selected_GO == selectedGameObject)
		selected_GO = nullptr;
}

void ModuleScene::AddChild(GameObject* child, GameObject* parent)
{
	if (parent == nullptr)
		parent = root;

	parent->children.push_back(child);
	child->parent = parent;
}

void ModuleScene::DrawGameObjects(GameObject* gameObject, GameObject* root)
{
	bool drawAgain = true;

	if (gameObject != root)
		gameObject->Draw();
	else
		drawAgain = true;

	if (drawAgain)
	{
		for (uint i = 0; i < gameObject->children.size(); i++)
		{
			DrawGameObjects(gameObject->children[i], root);
		}
	}
}


GameObject* ModuleScene::GetRoot()
{
	return root;
}

GameObject* ModuleScene::GetGameObjectByUUID(uint UUID) const
{
	GameObject* ret = nullptr;
	ret = GetGameObjectUUIDRecursive(UUID, root);
	return ret;
}

GameObject* ModuleScene::AddGameObject(const char* name)
{
	GameObject* ret = new GameObject();
	ret->name = name;
	ret->parent = root;
	root->children.push_back(ret);

	return ret;
}

GameObject* ModuleScene::AddGameObject(const char* name, GameObject* parent)
{
	GameObject* ret = new GameObject();
	ret->name = name;
	ret->parent = parent;
	parent->children.push_back(ret);

	return ret;
}

void ModuleScene::selectGameObject(GameObject* gameObject)
{
	if (selected_GO != nullptr)
		selected_GO->setSelected(false);

	selected_GO = gameObject;
	if (gameObject != nullptr)
		gameObject->setSelected(true);
}

void ModuleScene::ClearScene()
{
	App->console->AddLog("Clearing scene");
	for (int i = root->children.size() - 1; i >= 0; i--) {
		root->DestroyChildren(root->children[i]);
	}
	for (int i = root->components.size() - 1; i >= 0; i--) {
		root->DestroyComponent(root->components[i]->GetComponentType());
	}
}

void ModuleScene::CreateEmptyGameObject()
{
	GameObject* newGameObject = new GameObject();
	newGameObject->name = "Empty GameObject";
	newGameObject->SetParent(root);
	newGameObject->isStatic = false;

	float3 pos = float3::zero;
	float3 scale = float3::one;
	Quat rot = Quat::identity;

	//newGameObject->transform->position = pos;
	//newGameObject->transform->scale = scale;
	//newGameObject->transform->rotation = rot;
	//newGameObject->transform->localMatrix.Set(float4x4::FromTRS(pos, rot, scale));
}

bool ModuleScene::LoadGameObjects(GameObject* gameObject)
{
	bool ret = true;
	return ret;
}

bool ModuleScene::LoadScene(const char* file)
{
	return false;
}

bool ModuleScene::LoadSettings(JsonParser* data)
{
	bool ret = true;
	return ret;
}

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

uint ModuleScene::GetRandomUUID()
{
	return LCG().Int();
}

void ModuleScene::PlayScene(GameObject* gameObject, GameObject* root)
{
	for (uint i = 0; i < gameObject->children.size(); i++)
	{
		PlayScene(gameObject->children[i], root);
	}
}

void ModuleScene::StopScene(GameObject* gameObject, GameObject* root)
{
	for (uint i = 0; i < gameObject->children.size(); i++)
	{
		StopScene(gameObject->children[i], root);
	}
}

GameObject* ModuleScene::GetGameObjectUUIDRecursive(uint UUID, GameObject* go) const
{
	GameObject* ret = go;
	if (ret->GetUUID() == UUID) {
		return ret;
	}

	for (int i = 0; i < go->children.size(); i++) {
		ret = go->children[i];
		ret = GetGameObjectUUIDRecursive(UUID, ret);
		if (ret) {
			return ret;
		}
	}
	return nullptr;
}

void ModuleScene::UpdateGameObjects(GameObject* gameObject)
{
	gameObject->Update();
}
