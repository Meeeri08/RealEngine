#pragma once
#include "Globals.h"
#include "JsonParser.h"

class GameObject;

class Component
{
public:
	enum ComponentType {
		None = 0,
		Transformation,
		Mesh,
	};

public:
	Component(ComponentType type, GameObject* GO);
	~Component();

	virtual void Enable();
	virtual void Update();
	virtual void Disable();

	virtual Component::ComponentType GetComponentType();

	//virtual bool Save(JsonParser* data);
	//virtual bool Load(JsonParser* data);

public:

	GameObject* GO;
	bool isActive = true;
	uint component_UUID = 0;
};

