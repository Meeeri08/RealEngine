#pragma once
#include "Module.h"
#include "Globals.h"
#include "Component.h"

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

    //TODO: Improve system
    int _numVertices;
    int _numFaces;
    //int _index;

};