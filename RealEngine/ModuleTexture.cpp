#include "ModuleTexture.h"
#include <fstream>

ModuleTexture::ModuleTexture(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Texture";
}

ModuleTexture::~ModuleTexture()
{
}

bool ModuleTexture::Start()
{
	return true;
}

update_status ModuleTexture::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleTexture::CleanUp()
{
	return true;
}

bool ModuleTexture::DrawTexture()
{
	return false;
}

void ModuleTexture::ManageDroppedFile(char* droppedFile)
{
	bool exist = false;

	uint lenght = strlen(droppedFile);
	for (int i = 0; i < lenght; ++i)
	{
		if (droppedFile[i] == '\\')
			droppedFile[i] = '/';
	}
	
	//// .....
}
