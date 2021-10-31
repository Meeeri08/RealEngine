#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"


#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

#include <vector>



class Mesh 
{
public:
	
    aiMesh* mesh;
    float* vertex_id;
    float* normal_id;
    float* tex_id;

    int num_vex;

 
    void Render();
    int Init();

    Mesh(aiMesh* aiMesh);
    ~Mesh();
};
