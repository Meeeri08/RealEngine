#pragma once
//#include "Module.h"
#include "GameObject.h"
#include "MathGeoLib/src/MathGeoLib.h"
#include <vector>

class ModuleScene : public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	GameObject* CreateGameObject(std::string name, float3 position = { 0,0,0 }, Quat rotation = { 0,0,0,1 }, float3 scale = { 1,1,1 }, GameObject* parent = nullptr, char* mesh_path = nullptr, char* texture_path = nullptr);
	void DestroyGameObject(GameObject* selectedGameObject);
	void AddChild(GameObject* child, GameObject* parent = nullptr);

	void DrawGameObjects(GameObject* gameObject, GameObject* root);
	void FrustumCulling(GameObject* gameObject, GameObject* root);

	GameObject* GetRoot();
	GameObject* GetGameObjectByUUID(uint UUID) const;
	GameObject* AddGameObject(const char* name);
	GameObject* AddGameObject(const char* name, GameObject* parent);
	void selectGameObject(GameObject* gameObject);
	void ClearScene();

	void CreateEmptyGameObject();

	void PlayScene(GameObject* gameObject, GameObject* root);
	void StopScene(GameObject* gameObject, GameObject* root);

private:
	GameObject* GetGameObjectUUIDRecursive(uint UUID, GameObject* go) const;
	void UpdateGameObjects(GameObject* gameObject);

public:
	GameObject* root;
	GameObject* selected_GO;

	bool inGame;


};

