#include "ModuleFile.h"

ModuleFile::ModuleFile(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleFile::~ModuleFile()
{
}

bool ModuleFile::Exists(const char* path) const
{
	return false;
}
