#pragma once
#include "Component.h"
#include "JsonParser.h"
#include "Application.h"

#include <vector>
#include <string>

class GameObject
{
public:
	GameObject();
	~GameObject();

	Component* CreateComponent(Component::ComponentType type);
	void DestroyComponent(Component::ComponentType type);
	void Draw();
	Component* GetComponent(Component::ComponentType type);
	void GetComponents(Component::ComponentType type, std::vector<Component*>& comp);
	

	void SetParent(GameObject* parent);
	void setSelected(bool selected);
	void setChildSelected(bool selected);
	void AddChildren(GameObject* child);
	void DestroyChildren(GameObject* toDestroy);

	bool Update();
	bool Save(JsonParser* data);
	bool Load(JsonParser* data);

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
	
	std::string name;
	std::vector<Component*> components;
	std::vector<GameObject*> children;
	GameObject* parent;

private:
	uint parentUUID;
	uint UUID;
};

