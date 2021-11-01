#pragma once
#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "WindowConfiguration.h"
#include "GameObject.h"
#include "Transformation.h"

#include "MathGeoLib/src/MathGeoLib.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl2.h"

class Transformation;
class Mesh;

class InspectorWindow : WindowConfiguration
{

public:
	InspectorWindow();
	~InspectorWindow();

	void Draw(Application* App);
	void DrawTransform(Transformation* transformation);

public:

	char name[256];
	bool isActive;

};

