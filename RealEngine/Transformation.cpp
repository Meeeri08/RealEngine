#include "Transformation.h"

Transformation::Transformation(Component::ComponentType type, GameObject* GO) :Component(type, GO)
{
	this->GO = GO;
	position = { 0.0f,0.0f,0.0f };
	scale = { 1.0f,1.0f,1.0f };
	rotationVector = { 0.0f,0.0f,0.0f }; // user-friendly
	quatRotation = { 0.0f,0.0f,0.0f,1.0f }; // used for calculations

	localMatrix = float4x4::identity;
	globalMatrix = float4x4::identity;
}

Transformation::~Transformation(){}

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

Quat Transformation::GetQuatRotation()
{
	return quatRotation;
}

void Transformation::SetPosition(float3 position)
{
	this->position = position;
	CalculateMatrix();
}

void Transformation::SetScale(float3 scale)
{
	this->scale = scale;
	CalculateMatrix();
}

void Transformation::SetRotation(float3 rotation)
{
	rotationVector = rotation;
	this->quatRotation = Quat::FromEulerXYZ(rotationVector.x * DEGTORAD, rotationVector.y * DEGTORAD, rotationVector.z * DEGTORAD);
	CalculateMatrix();
}

void Transformation::SetQuatRotation(Quat quatRotation)
{
	this->quatRotation = quatRotation;
	rotationVector = this->quatRotation.ToEulerXYZ() * RADTODEG;
	CalculateMatrix();
}

void Transformation::CalculateMatrix()
{
	localMatrix.Set(float4x4::FromTRS(position, quatRotation, scale));
}

/*
bool Transformation::Save(JsonParser* data)
{
	bool ret = true;

	data->AddString("Component", "Transform");
	data->AddInt("Type", Component::ComponentType::Transformation);

	return ret;
}

bool Transformation::Load(JsonParser* data)
{
	bool ret = true;
	component_UUID = data->GetUInt("UUID");

	return ret;
}
*/