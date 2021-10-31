#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"


#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

#include <vector>


struct Vertex
{
	// Index
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	// Vertex
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;


	// Texture
	uint id_tex = 0;
	uint num_tex = 0;
	uint texture_id = 0;
	float* tex = nullptr;

	// Buffers
	void GenerateBuffer();

	// Draw Mesh 
	void LoadMesh();

};

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
	std::vector<Vertex*> vertex;


};
