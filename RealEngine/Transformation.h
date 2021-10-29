#pragma once
#include "Globals.h"
#include "Component.h"
#include "GameObject.h"

#include "MathGeoLib/src/MathGeoLib.h"

class Transformation : public Component
{
public:

	Transformation(Component::ComponentType type, GameObject* owner);
	~Transformation();

public:

	Component::ComponentType GetComponentType() override;
	
	void SetPosition(float3 position);
	void SetScale(float3 scale);
	void SetRotation(float3 rotation);
	void SetQuaternionRotation(Quat quadRotation);

	float3 GetPosition();
	float3 GetScale();
	float3 GetEulerRotation();
	Quat GetQuaternionRotation();

	void RecalculateMatrix();

	bool Save(JsonParser* data) override;
	bool Load(JsonParser* data) override;

public:

	float3 position = {0.0f,0.0f,0.0f};
	float3 scale = {1.0f,1.0f,1.0f};
	float3 rotationVector = {0.0f,0.0f,0.0f};
	Quat rotation = {0.0f,0.0f,0.0f,1.0f};

	float4x4 localMatrix = float4x4::identity;
	float4x4 globalMatrix = float4x4::identity;

	bool isChanged;
};


