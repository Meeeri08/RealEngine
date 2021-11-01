#pragma once

#include "WindowConfiguration.h"
#include "Application.h"
#include "GameObject.h"

#include <vector>
#include <string>

class HierarchyWindow : WindowConfiguration
{
public:
	HierarchyWindow();
	~HierarchyWindow();

	void Draw(Application* App);
	void DrawGameObject(Application* App, GameObject* gameObject, ImGuiTreeNodeFlags default_flags, GameObject* root);

public:

	bool isActive;
	Application* App;
	std::vector<GameObject*> gameObjects;
};