#pragma once
#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl2.h"


class InspectorWindow
{

public:
	InspectorWindow();
	~InspectorWindow();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

};

