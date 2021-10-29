#pragma once

#include "Module.h"
#include "Globals.h"

#include <string>

class ModuleFile : public Module
{
	ModuleFile(Application* app, bool start_enabled = true);
	~ModuleFile();

	bool AddPath(const char* path);
	uint WriteFile(const char* fileName, const void* data, uint bytes);
	uint ReadFile(const char* fileName, char** data);
	void RemoveFile(const char* path);
	bool Copy(const char* source, const char* destination);
	void GetNameFromPath(const char* full_path, std::string* path, std::string* file, std::string* fileWithExtension, std::string* extension) const;
	
};

