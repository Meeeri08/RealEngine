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

void ModuleTexture::ManageDroppedTexture(char* droppedFile)
{
	bool exist = false;

	uint lenght = strlen(droppedFile);
	for (int i = 0; i < lenght; ++i)
	{
		if (droppedFile[i] == '\\')
			droppedFile[i] = '/';
	}
	/*
	if (App->file->Exists(droppedFile)) {
		App->console->AddLog("This texture already exists in Assets folder!")
	}
	
	else {
		std::string path = "Assets/Textures/";
		std::string name;

		if (droppedFile != nullptr)
		{
			std::string nwFullPath = droppedFile;
			uint lenght = strlen(nwFullPath.c_str());
			for (int i = 0; i < lenght; ++i)
			{
				if (nwFullPath[i] == '\\')
					nwFullPath[i] = '/';
			}

			size_t posSlash = nwFullPath.find_last_of("\\/");
			size_t posDot = nwFullPath.find_last_of(".");
			
			if (&name != nullptr) {
				if (posSlash < nwFullPath.length()) {
					*&name = nwFullPath.substr(posSlash + 1);
				}
				else
					*&name = nwFullPath;
			}
		}
		path += name;
		//App->file->Copy(droppedFile, path.c_str());
	}
	*/
}
