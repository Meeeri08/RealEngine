#include "FBXLoader.h"
#include "GameObject.h"
#include "ModuleFile.h"
#include "Application.h"

FBXLoader::FBXLoader(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "sceneLoader";
}

FBXLoader::~FBXLoader()
{
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

GameObject* FBXLoader::ImportNodeRecursive(aiNode* node, const aiScene* scene, GameObject* parent)
{
	GameObject* nodeGO = nullptr;

	if (node->mMetaData != nullptr) { // to get the gameobject not a transform matrix

		nodeGO = new GameObject();
		nodeGO->name = node->mName.C_Str();
		nodeGO->SetParent(parent);

		aiVector3D position;
		aiQuaternion rotation;
		aiVector3D scale;
		node->mTransformation.Decompose(scale, rotation, position);

		nodeGO->transformation->SetPosition(float3(position.x, position.y, position.z));
		nodeGO->transformation->SetScale(float3(scale.x, scale.y, scale.z));
		nodeGO->transformation->SetQuaternionRotation(Quat(rotation.x, rotation.y, rotation.z, rotation.w));

		if (node->mNumMeshes > 0)
		{
			for (uint i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

				//C_Material* compMat = (C_Material*)nodeGO->CreateComponent(Component::Type::Material);

				/*

				if (material)
				{
					if (compMat != nullptr)
					{
						bool error, col, mater;
						error = col = mater = false;

						aiString texturePath;

						aiColor3D color = aiColor3D();
						material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
						if (!color.IsBlack())
						{
							compMat->colors = { color.r, color.g, color.b };
							col = true;
						}

						aiReturn ret = material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
						
						}
						else {

							LOG("Error loading texture from fbx. Error: %s", aiGetErrorString());
						}
					}
					else {
						RELEASE(compMat);
					}
				}

				std::string meshName = nodeGO->name;

				Mesh* newMesh = nullptr;

				if (newMesh != nullptr)
				{
					if (compMat)
					{
						newMesh->SetMaterial(compMat);
					}
				}
				else {
					RELEASE(newMesh);
				}

				compMat = nullptr;
				newMesh = nullptr;
				mesh = nullptr;
				material = nullptr;
				*/
			}
		}
	}
	if (!nodeGO) { nodeGO = parent; }
	for (uint i = 0; i < node->mNumChildren; i++) // recursivity
	{
		GameObject* child = ImportNodeRecursive(node->mChildren[i], scene, nodeGO);

	}
	return nodeGO;
}

void FBXLoader::LoadFBXScene(const char* FBXpath)
{
	std::string fullFBXPath;// = MODELS_PATH;
	fullFBXPath += FBXpath;

	std::string modelName;

	//App->file->GetNameFromPath(fullFBXPath.c_str(), nullptr, &modelName, nullptr, nullptr);

	const aiScene* scene = aiImportFile(fullFBXPath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene == nullptr) {
		scene = aiImportFile(FBXpath, aiProcessPreset_TargetRealtime_MaxQuality);
		if (scene == nullptr){
			App->console->AddLog("Error loading fbx from Assets/Models folder.");
			aiReleaseImport(scene);
			return;
		}
	}
	else {
		GameObject* GO;
		GO = App->scene->AddGameObject(modelName.c_str());

		GameObject* GOchild = ImportNodeRecursive(scene->mRootNode, scene, GO);
  
		GOchild = nullptr;
		GO = nullptr;
		aiReleaseImport(scene);
		App->console->AddLog("Loaded succesfully fbx from %s.", FBXpath);
	}
}
