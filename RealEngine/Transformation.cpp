#include "Transformation.h"

Transformation::Transformation(Component::ComponentType type, GameObject* owner) :Component(type, owner)
{
	this->owner = owner;
	position = { 0.0f,0.0f,0.0f };
	rotationVector = { 0.0f,0.0f,0.0f }; // user-friendly
	scale = { 1.0f,1.0f,1.0f };
	rotation = { 0.0f,0.0f,0.0f,1.0f }; // used for calculations

	localMatrix = float4x4::identity;
	globalMatrix = float4x4::identity;
}

Transformation::~Transformation()
{
}

Component::ComponentType Transformation::GetComponentType()
{
	return Component::ComponentType::Transformation;
}

float3 Transformation::GetPosition()
{
	return position;
}

float3 Transformation::GetScale()
{
	return scale;
}

float3 Transformation::GetEulerRotation()
{
	return rotationVector;
}

void Transformation::SetPosition(float3 position)
{
	this->position = position;
	RecalculateMatrix();
}

void Transformation::SetScale(float3 scale)
{
	this->scale = scale;
	RecalculateMatrix();
}

void Transformation::SetRotation(float3 rotation)
{
	rotationVector = rotation;
	this->rotation = Quat::FromEulerXYZ(rotationVector.x * DEGTORAD, rotationVector.y * DEGTORAD, rotationVector.z * DEGTORAD);
	RecalculateMatrix();
}

void Transformation::SetQuaternionRotation(Quat quatRotation)
{
	rotation = quatRotation;
	rotationVector = rotation.ToEulerXYZ() * RADTODEG;
	RecalculateMatrix();
}

Quat Transformation::GetQuaternionRotation()
{
	return rotation;
}

void Transformation::RecalculateMatrix()
{
	localMatrix.Set(float4x4::FromTRS(position, rotation, scale));
}

bool Transformation::Save(JsonParser* data)
{
	bool ret = true;

	data->AddString("Component", "Transform");
	data->AddInt("Type", Component::ComponentType::Transformation);

	//data->AddVector3("Position", position);
	//data->AddVector3("Scale", scale);
	//data->AddVector3("Rotation", rotationVector);
	//data->AddQuat("Rotation_Quat", rotation);
	//data->Add4x4("Local_Matrix", localMatrix);
	//data->Add4x4("Global_Matrix", globalMatrix);

	return ret;
}

bool Transformation::Load(JsonParser* data)
{
	bool ret = true;
	component_UUID = data->GetUInt("UUID");

	//SetPosition(data->GetVector3("Position", position));
	//SetRotation(data->GetVector3("Rotation", rotationVector));
	//SetScale(data->GetVector3("Scale", scale));

	return ret;
}
