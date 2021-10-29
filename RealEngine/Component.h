#pragma once
#include "Globals.h"
#include "JsonParser.h"

class Component
{
public:
	enum ComponentType {
		None = 0,
		Mesh,
		Material,
		Camera,
		Light,
		Transformation
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

	virtual void SetResource(uint resource) {};

	//virtual Resource* GetResource() const;
	uint GetResourceUUID()const; //{ return component_UUID; }

protected:

	uint component_UUID = 0;

public:

	GameObject* owner;
	bool isActive = true;
};

