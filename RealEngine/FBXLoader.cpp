#include "FBXLoader.h"
#include "Application.h"
#include "GameObject.h"
#include "ModuleScene.h"

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

void FBXLoader::LoadFBX(const char* FBXpath)
{
	//Timer loadTime;

	std::string fullFBXPath;// = MODELS_PATH;
	fullFBXPath += FBXpath;

	std::string modelName = "TestingFBX";

	const aiScene* scene = aiImportFile(fullFBXPath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene == nullptr) {
		//LOG("Error loading fbx from Assets/Models folder.");
		aiReleaseImport(scene);

		return;
	}
	else {
		GameObject* GO = new GameObject();
		GO->name = name;
		GO->parent = App->scene->root;
		App->scene->root->AddChildren(GO);
		//GO = App->scene->CreateGameObject(modelName.c_str());

		//GameObject* GOchild = ImportNodeRecursive(scene->mRootNode, scene, GO);


		//GOchild = nullptr;
		//GO = nullptr;
		aiReleaseImport(scene);
	}
}




