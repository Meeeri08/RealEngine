#pragma once
#include "Component.h"
#include "JsonParser.h"
#include "Application.h"
#include "Transformation.h"
#include "Mesh.h"

#include <vector>
#include <string>

class GameObject
{

public:

	GameObject();
	~GameObject();

	Component* CreateComponent(Component::ComponentType type);
	void DestroyComponent(Component::ComponentType type);

	Component* GetComponent(Component::ComponentType type);

	void SetParent(GameObject* parent);
	void SetSelected(bool selected);
	void SetChildSelected(bool selectedChild);

	void AddChildren(GameObject* child);
	void DestroyChildren(GameObject* toDestroy);

	bool Update();
	bool Save(JsonParser* data);
	bool Load(JsonParser* data);

	void ChangeName(std::string name);

	bool GetIsSelected();
	void Select();
	void Unselect();

	uint GenerateUUID();
	uint GetUUID();
	uint GetParentUUID();

public:

	bool isActive;
	bool isSelected;
	bool isStatic;
	bool wantToDelete;
	bool selectedChild;

	Application* App;
	Transformation* transformation;
	Mesh* mesh;

	std::string name;
	std::vector<Component*> components;
	std::vector<GameObject*> children;
	GameObject* parent;

private:
	uint parentUUID;
	uint UUID;
};

