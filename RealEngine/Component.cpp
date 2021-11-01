#include "Component.h"
#include "GameObject.h"

Component::Component(ComponentType type, GameObject* GO)
{
	isActive = true;
	this->GO = GO;
	component_UUID = GO->GenerateUUID();
}

Component::~Component(){}

void Component::Enable(){}
void Component::Update(){}
void Component::Disable(){}

Component::ComponentType Component::GetComponentType()
{
	return Component::ComponentType::None;
}

/*
bool Component::Save(JsonParser* data){}
bool Component::Load(JsonParser* data){}
*/