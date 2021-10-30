#pragma once
#include "Module.h"
#include "Globals.h"

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

	void DrawGameObjects(GameObject* gameObject, GameObject* root);
	void UpdateGameObjects(GameObject* gameObject);

	GameObject* GetRoot();

public:

	ImGuizmo::OPERATION guizmoOperation;
	bool inGame;

private:
	GameObject* root;
	GameObject* selected_GO;
};
