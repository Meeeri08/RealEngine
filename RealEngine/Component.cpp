#include "Component.h"
#include "GameObject.h"

Component::Component(ComponentType type, GameObject* owner)
{
	isActive = true;
	this->owner = owner;

	component_UUID = owner->GenerateUUID();
}

Component::~Component()
{
}

void Component::Enable()
{
}

void Component::Update()
{
}

void Component::Disable()
{
}

Component::ComponentType Component::GetComponentType()
{
	return Component::ComponentType::None;
}

bool Component::Save(JsonParser* data)
{
	bool ret = true;

	return ret;
}

bool Component::Load(JsonParser* data)
{
	return true;
}