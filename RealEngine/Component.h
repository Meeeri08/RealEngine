#pragma once
#include "Globals.h"
#include "JsonParser.h"
//#include "GameObject.h"

class GameObject;

class Component
{
public:
	enum ComponentType {
		None = 0,
		Transformation,
	};

public:
	Component(ComponentType type, GameObject* owner);
	~Component();

	virtual void Enable();
	virtual void Update();
	virtual void Disable();
	virtual Component::ComponentType GetComponentType();

	virtual bool Save(JsonParser* data);
	virtual bool Load(JsonParser* data);

protected:
	uint component_UUID = 0;
public:

	GameObject* owner;
	bool isActive = true;
};

