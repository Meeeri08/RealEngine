#pragma once
#include "Module.h"
#include "Globals.h"
#include "Component.h"
#include "glmath.h"
#include "Light.h"

#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

#include <vector>

class Mesh : public Component
{
public:

    Mesh(Component::ComponentType type, aiMesh* aiMesh, GameObject* owner);
	Mesh(Component::ComponentType type);
    ~Mesh();

    void Render();
    int Init();

public:

	aiMesh* mesh;
	
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	// Vertex
	float* vertex_id; // unique vertex in VRAM
	int num_vertex;
	float* vertex = nullptr;

	// Texture
	float* tex_id;
	uint num_tex = 0;
	uint texture_id = 0;
	float* tex = nullptr;

	// Normals
	float* normal_id;
	float* normals = nullptr;
};