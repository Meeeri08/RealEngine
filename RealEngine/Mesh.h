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

class Mesh
{
public:

	Mesh(aiMesh* mesh);
    ~Mesh();

    void Render();
    int Init();

public:

    aiMesh* mesh;
    float* vertex_id;
    float* normal_id;
    float* tex_id;
    int num_vertex;
};