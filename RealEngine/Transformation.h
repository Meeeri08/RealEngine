#pragma once

#include "Globals.h"
#include "Component.h"

#include "MathGeoLib/src/MathGeoLib.h"

class Transformation : public Component
{
public:

	Transformation(Component::ComponentType type, GameObject* GO);
	~Transformation();

public:

	Component::ComponentType GetComponentType() override;

	float3 GetPosition();
	float3 GetScale();
	float3 GetEulerRotation();
	Quat GetQuatRotation();

	void SetPosition(float3 position);
	void SetScale(float3 scl);
	void SetRotation(float3 rot);
	void SetQuatRotation(Quat quatRot);

	void CalculateMatrix();

	//bool Save(JsonParser* data) override;
	//bool Load(JsonParser* data) override;

public:

	float3 position;
	float3 scale;
	float3 rotationVector;
	Quat quatRotation;

	float4x4 localMatrix;
	float4x4 globalMatrix;
};

