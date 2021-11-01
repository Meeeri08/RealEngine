#include "glew/include/glew.h"
#include <SDL_opengl.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "ModuleLoader.h"
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "ModuleSceneIntro.h"
#include <cmath>

#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH  64

ModuleLoader::ModuleLoader(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    name = "module_loader";
}

// Destructor
ModuleLoader::~ModuleLoader()
{}

// Called before render is available
bool ModuleLoader::Init()
{
    App->console->AddLog("Loading Module Loader");
    bool ret = true;

     //checker texture
    GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
    for (int i = 0; i < CHECKERS_HEIGHT; i++) {
        for (int j = 0; j < CHECKERS_WIDTH; j++) {
            int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
            checkerImage[i][j][0] = (GLubyte)c;
            checkerImage[i][j][1] = (GLubyte)c;
            checkerImage[i][j][2] = (GLubyte)c;
            checkerImage[i][j][3] = (GLubyte)255;
        }
    }

    //Loading FBX
    App->fbxLoader->Load("Assets/Models/BakerHouse.fbx");

    return ret;
}

// PreUpdate: clear buffer
update_status ModuleLoader::PreUpdate(float dt)
{
    // Stream log messages to Debug window
    struct aiLogStream stream;
    stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
    aiAttachLogStream(&stream);


    for (int i = 0; i < meshes.size(); ++i)
    {
        meshes[i]->Render();
    }

    return UPDATE_CONTINUE;
}

update_status ModuleLoader::Update(float dt)
{
    return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleLoader::PostUpdate(float dt)
{
    return UPDATE_CONTINUE;
}

bool ModuleLoader::CleanUp()
{
    App->console->AddLog("Destroying 3D Renderer");

    // detach log stream
    aiDetachAllLogStreams();

    return true;
}

void ModuleLoader::Load(char* FBXpath)
{
    std::string fullFBXPath = FBXpath;
    std::string modelName = GenerateNameFromPath(fullFBXPath);

    const aiScene* scene = aiImportFile(fullFBXPath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
    if (scene != nullptr && scene->HasMeshes())
    {
        GameObject* GO = new GameObject();
        GO->name = modelName;
        GO->parent = App->scene_intro->GetRoot();
        App->scene_intro->GetRoot()->AddChildren(GO);

        for (int i = 0; i < scene->mNumMeshes; ++i)
        {
            aiMesh* mesh = scene->mMeshes[i];
            Mesh* mM = new Mesh(mesh);
            int vertex= mM->Init(); 
            App->console->AddLog("New mesh with %d vertices", vertex);

            meshes.push_back(mM);
        }
    }
    else
        App->console->AddLog("Error loading scene %s", FBXpath);
}

std::string ModuleLoader::GenerateNameFromPath(std::string path)
{
    std::string name = "";
    std::string normalizedPath = path;

    //Normalize path
    for (int i = 0; i < path.length(); i++)
    {
        if (normalizedPath[i] == '\\')
            normalizedPath[i] = '/';
    }

    size_t posSlash = normalizedPath.find_last_of("\\/");
    size_t posDot = normalizedPath.find_last_of(".");

    for (int i = posSlash + 1; i < posDot; i++) {
        name += normalizedPath[i];
    }
    return name;
}