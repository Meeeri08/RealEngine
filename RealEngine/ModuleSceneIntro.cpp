#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "GameObject.h"
#include "Primitive.h"
#include "ModuleRenderer3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "SceneIntro";
	root = new GameObject();
	root->name = "root";
	selectedGameObject = nullptr;
	inGame = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	App->console->AddLog("Loading Intro assets");
	ImGuizmo::Enable(false);
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	return ret;
}

// Update: draw background
update_status ModuleSceneIntro::Update(float dt)
{
	PrimitivePlane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	// checking drawing 
	/*glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 10.f, 0.f);
	glEnd();
	glLineWidth(5.0f);*/

	//Direct mode drawing

	if (App->scene_intro->selectedGameObject != nullptr)
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
	//Wireframe
	App->renderer3D->SetWireframeMode();
	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	//DrawGameObjects(GetRoot(), GetRoot());
	UpdateGameObject(GetRoot());
	return UPDATE_CONTINUE;
}


// Load assets
bool ModuleSceneIntro::CleanUp()
{
	App->console->AddLog("Unloading Intro scene");

	return true;
}

void ModuleSceneIntro::AddChild(GameObject* child, GameObject* parent)
{
	if (parent == nullptr)
		parent = root;

	parent->children.push_back(child);
	child->parent = parent;
}

void ModuleSceneIntro::selectGameObject(GameObject* gameObject)
{
	if (selectedGameObject != nullptr)
		selectedGameObject->setSelected(false);

	selectedGameObject = gameObject;
	if (gameObject != nullptr)
		gameObject->setSelected(true);
}

GameObject* ModuleSceneIntro::CreateGameObject(std::string name, float3 position, Quat rotation, float3 scale, GameObject* parent, char* mesh_path, char* texture_path)
{
	GameObject* newGameObject = nullptr;
	newGameObject = new GameObject();
	newGameObject->ChangeName(name);

	if (newGameObject != nullptr)
		AddChild(newGameObject, parent);

	newGameObject->transformation->SetPosition(position);
	newGameObject->transformation->SetQuaternionRotation(rotation);
	newGameObject->transformation->SetScale(scale);
	newGameObject->transformation->isChanged = true;

	return newGameObject;
}

void ModuleSceneIntro::DrawGameObjects(GameObject* gameObject, GameObject* root)
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

void ModuleSceneIntro::UpdateGameObject(GameObject* gameObject)
{
	gameObject->Update();
}

void ModuleSceneIntro::DestroyGameObject(GameObject* selectedGameObject)
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

	if (this->selectedGameObject == selectedGameObject)
		this->selectedGameObject = nullptr;
}


GameObject* ModuleSceneIntro::GetRoot()
{
	return root;
}

GameObject* ModuleSceneIntro::GetGameObjectByUUID(uint UUID) const
{
	GameObject* ret = nullptr;
	ret = GetGameObjectUUIDRecursive(UUID, root);
	return ret;
}

GameObject* ModuleSceneIntro::GetGameObjectUUIDRecursive(uint UUID, GameObject* object) const
{
	GameObject* ret = object;
	if (ret->GetUUID() == UUID) {
		return ret;
	}

	for (int i = 0; i < object->children.size(); i++) {
		ret = object->children[i];
		ret = GetGameObjectUUIDRecursive(UUID, ret);
		if (ret) {
			return ret;
		}
	}
	return nullptr;
}
