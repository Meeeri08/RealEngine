#pragma once
#include "Module.h"
#include "Application.h"

class ModuleFile : public Module
{
public:

	ModuleFile(Application* App, bool start_enabled = true);
	~ModuleFile();

	bool Exists(const char* path) const;
};
