#pragma once
#include "Module.h"
#include "Globals.h"

#include "MathGeoLib/src/MathGeoLib.h"
#include "ImGuizmo/ImGuizmo.h"

class GameObject;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start() override;
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void AddChild(GameObject* child, GameObject* parent = nullptr);

	void selectGameObject(GameObject* gameObject);

	GameObject* CreateGameObject(std::string name, float3 position = { 0,0,0 }, Quat rotation = { 0,0,0,1 }, float3 scale = { 1,1,1 }, GameObject* parent = nullptr, char* mesh_path = nullptr, char* texture_path = nullptr);
	void DrawGameObjects(GameObject* gameObject, GameObject* root);
	void UpdateGameObject(GameObject* gameObject);
	void DestroyGameObject(GameObject* selectedGameObject);

	GameObject* GetRoot();
	GameObject* GetGameObjectByUUID(uint UUID) const;

	GameObject* GetGameObjectUUIDRecursive(uint UUID, GameObject* go) const;

public:

	ImGuizmo::OPERATION guizmoOperation;
	bool inGame;

	GameObject* root;
	GameObject* selectedGameObject;
};
