#pragma once

#include "Globals.h"
#include "Module.h"
#include "ModuleFile.h"
#include "GameObject.h"

#include "MathGeoLib/src/MathGeoLib.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/scene.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

struct Vertex;

class FBXLoader : public Module{

public:

	FBXLoader(Application* app, bool start_enabled = true);
	~FBXLoader();

	bool Start()override;
	update_status Update(float dt)override;
	bool CleanUp()override;

	GameObject* ImportNodeRecursive(aiNode* node, const aiScene* scene, GameObject* parent);
	void LoadFBXScene(const char* path);

};

