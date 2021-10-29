#include "FBXLoader.h"


FBXLoader::FBXLoader(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "scene_loader";

}

FBXLoader::~FBXLoader() {

}

bool FBXLoader::Start()
{
	return true;
}

update_status FBXLoader::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool FBXLoader::CleanUp()
{
	return true;
}




