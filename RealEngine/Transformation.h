#pragma once

#include "Globals.h"
#include "Component.h"

#include "MathGeoLib/src/MathGeoLib.h"

class Transformation : public Component
{
public:

	Transformation(Component::ComponentType type, GameObject* owner);
	~Transformation();

public:

	Component::ComponentType GetComponentType() override;

	float3 GetPosition();
	float3 GetScale();
	float3 GetEulerRotation();
	Quat GetQuaternionRotation();

	void SetPosition(float3 pos);
	void SetScale(float3 scl);
	void SetRotation(float3 rot);
	void SetQuaternionRotation(Quat quatRot);

	void RecalculateMatrix();

	bool Save(JsonParser* data) override;
	bool Load(JsonParser* data) override;

public:
	float3 position;
	float3 rotationVector;
	float3 scale;
	Quat rotation;

	float4x4 localMatrix;
	float4x4 globalMatrix;

	bool isChanged;
};

