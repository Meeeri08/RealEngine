#pragma once
#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "WindowConfiguration.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl2.h"


class InspectorWindow : WindowConfiguration
{

public:
	InspectorWindow();
	~InspectorWindow();

	void Draw() override;
	void SetShowWindow() override;
	bool GetShowWindow() override;

	char name[256];
	bool isActive;

};

