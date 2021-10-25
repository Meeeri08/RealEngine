#pragma once

#include "WindowConfiguration.h"
#include "Application.h"
#include "GameObject.h"

#include <vector>

class HierarchyWindow : WindowConfiguration
{
public:
	HierarchyWindow();
	~HierarchyWindow();

	void Draw() override;
	void DrawGameObject(GameObject* gameObject, ImGuiTreeNodeFlags default_flags, GameObject* root);
	void SetShowWindow() override;
	bool GetShowWindow() override;

public:

	bool isActive;
	bool openPopUp;
	Application* App;

	std::vector<GameObject*> selectedGameObjects;
};
