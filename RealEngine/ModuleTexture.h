#pragma once
#include "Globals.h"
#include "Module.h"
#include "Application.h"

class ModuleTexture : public Module
{
public: 

	ModuleTexture(Application* app, bool start_enabled = true);
	~ModuleTexture();

	bool Start()override;
	update_status Update(float dt)override;
	bool CleanUp()override;

	bool DrawTexture();
	void ManageDroppedFile(char* droppedFile);
};

