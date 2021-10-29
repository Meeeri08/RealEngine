#include "GameObject.h"

GameObject::GameObject()
{
	isActive = true;
	isSelected = false;
	isStatic = false;
	wantToDelete = false;
	selectedChild = false;

	parentUUID = 0;
	UUID = GenerateUUID();
}

GameObject::~GameObject()
{
}

Component* GameObject::CreateComponent(Component::ComponentType type)
{
	Component* component = nullptr;

	switch (type)
	{
	case Component::ComponentType::None:
		break;
	case Component::ComponentType::Mesh:

		break;
	case Component::ComponentType::Material:

		break;
	case Component::ComponentType::Camera:

		break;
	default:
		break;
	}
	if (component)
		components.push_back(component);

	return component;
}

void GameObject::DestroyComponent(Component::ComponentType type)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (type == components[i]->GetComponentType())
		{
			components[i]->Disable();
		}
	}
}

void GameObject::Draw()
{
}

Component* GameObject::GetComponent(Component::ComponentType type)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (type == components[i]->GetComponentType())
		{
			return components[i];
		}
	}

	return nullptr;
}

void GameObject::GetComponents(Component::ComponentType type, std::vector<Component*>& comp)
{
}

void GameObject::SetParent(GameObject* parent)
{
}

void GameObject::setSelected(bool selected)
{
}

void GameObject::setChildSelected(bool selected)
{
}

void GameObject::AddChildren(GameObject* child)
{
}

void GameObject::DestroyChildren(GameObject* toDestroy)
{
}

bool GameObject::Update()
{
	bool ret = true;

	for (size_t i = 0; i < components.size(); i++) {
		components[i]->Update();
	}

	for (size_t i = 0; i < children.size(); i++) {
		if (children[i]->isActive) {
			children[i]->Update();
		}
	}

	return ret;
}

bool GameObject::Save(JsonParser* data)
{
	bool ret = true;

	data->AddString("Name", name.c_str());
	data->AddBool("Active", isActive);
	data->AddBool("Static", isStatic);
	data->AddArray("Components");

	if (!children.empty()) {
		data->AddArray("Children");
	}
	for (size_t i = 0; i < children.size(); i++) {
		JsonParser childrenData;
		children[i]->Save(&childrenData);
		data->AddArrayChild(childrenData);
	}
	return ret;

	for (size_t i = 0; i < components.size(); i++)
	{
		JsonParser componentsData;
		components[i]->Save(&componentsData);
		data->AddArrayChild(componentsData);
	}
}

bool GameObject::Load(JsonParser* data)
{
	bool ret = true;

	UUID = data->GetUInt("UUID");
	parentUUID = data->GetUInt("ParentUUID");
	name = data->GetString("Name", "Unnamed");
	isActive = data->GetBool("Active", true);
	isStatic = data->GetBool("Static", false);

	JsonParser elem;

	/*

	GameObject* parent = App->scene->GetGameObjectByUUID(parentUUID);
	if (parent != nullptr)
		SetParent(parent);
	else
		SetParent(App->scene->GetRoot());
		*/

		//Load components
	int component_num = data->GetNumElementsInArray("Components");
	if (component_num == -1) {
		App->console->AddLog("Warning. No components detected for this gameObject");
	}

	for (int i = 0; i < component_num; i++) {
		//elem = data->GetArray("Components", i);
		Component::ComponentType type = (Component::ComponentType)elem.GetInt("Type");
		if (type != Component::ComponentType::None) {
			Component* comp = CreateComponent(type);
			comp->Load(&elem);
			App->console->AddLog("Component loaded: %i", type);
		}
		else {
			App->console->AddLog("Cannot load components correctly. Component type: NOTYPE ");
		}
	}

	//Load childs

	int childs_num = data->GetNumElementsInArray("Childs");
	if (childs_num == -1) {
		App->console->AddLog("Warning. No components detected for this gameObject");
	}

	for (int i = 0; i < childs_num; i++) {
		//elem = data->GetArray("Children", i);
		GameObject* go = new GameObject();
		go->Load(&elem);
	}

	return ret;
}

void GameObject::ChangeName(std::string name)
{
	this->name = name;
}

bool GameObject::GetIsSelected()
{
	return isSelected;
}

void GameObject::Select()
{
	isSelected = true;
}

void GameObject::Unselect()
{
	isSelected = false;
}

uint GameObject::GenerateUUID()
{
	return uint();
}

uint GameObject::GetUUID()
{
	return uint();
}

uint GameObject::GetParentUUID()
{
	return uint();
}
