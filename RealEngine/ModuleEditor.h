#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl2.h"
#include <gl/GL.h>
#include <vector>
#include <stdio.h>
#include <list>

class InspectorWindow;

class ModuleEditor : public Module
{
public:
	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

	bool show_demo_window = false;
	bool show_another_window = false;
	bool show_debug_window = false;
	bool show_configuration = false;
	bool show_toolbar = false;
	bool show_console = true;
	bool show_inspector = true;
	bool config = false;

	std::vector<float> fps_log;
	std::vector<float> ms_log;

	char appName[64];
	char orgName[64];
	
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	bool about_us = false;
	bool show_about_us = false;

	bool configuration = true;

	InspectorWindow* inspectorWindow;

};