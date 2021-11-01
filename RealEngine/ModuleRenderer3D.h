#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "Component.h"
#include "GameObject.h"

#define MAX_LIGHTS 8

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
	bool LoadSettings(JsonParser* data)override;
	bool SaveSettings(JsonParser* data)const override;

	void OnResize(int width, int height);

	bool show_demo_window = true;
	bool show_another_window = false;

	bool vsync = false;

	void capFps();
	void SetWireframeMode();

	void CalculateGlobalMatrix(GameObject* gameObject);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	//OpenGL Options
	bool depth_test = true;
	bool cull_face = true;
	bool lighting = true;
	bool color_material = true;
	bool texture_2D = true;
	bool wireframe = false;
};