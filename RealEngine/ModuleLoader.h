#pragma once
#include "Mesh.h"
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"


#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

#include <vector>



class ModuleLoader : public Module
{
public:
	ModuleLoader(Application* app, bool start_enabled = true);
	~ModuleLoader();

	bool Init() override;
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp() override;

	void Load(char* FBXpath);

	std::string GenerateNameFromPath(std::string path);
	std::vector<Mesh*> meshes;


};
