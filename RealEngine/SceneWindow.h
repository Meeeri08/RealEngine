#pragma once
#include "glew/include/glew.h"
#include "imgui/imgui.h"
#include "WindowConfiguration.h"

class SceneWindow : WindowConfiguration
{
	SceneWindow();
	~SceneWindow();

	void Draw(GLuint texture);

	void SetShowWindow() override;
	bool GetShowWindow() override; 
};


