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
    name = "scene_loader";
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
    App->fbxLoader->Load("Assets/BakerHouse.fbx");

    return ret;
}

// PreUpdate: clear buffer
update_status ModuleLoader::PreUpdate(float dt)
{

    // Stream log messages to Debug window
    struct aiLogStream stream;
    stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
    aiAttachLogStream(&stream);


    for (int i = 0; i < vertex.size(); ++i)
    {
        vertex[i]->LoadMesh();
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
    Vertex* ourMesh = new Vertex();
    std::string fullFBXPath = FBXpath;
    std::string modelName = GenerateNameFromPath(fullFBXPath);

   

    const aiScene* scene = aiImportFile(fullFBXPath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
    if (scene != nullptr && scene->HasMeshes())
    {
        GameObject* GO = new GameObject();
        GO->name = modelName;
        GO->parent = App->scene_intro->GetRoot();
        App->scene_intro->GetRoot()->AddChildren(GO);

        // Use scene->mNumMeshes to iterate on scene->mMeshes array

        for (int i = 0; i < scene->mNumMeshes; ++i)
        {
            //
            aiMesh* sceneM = scene->mMeshes[i];

            // copy vertices
            ourMesh->num_vertex = sceneM->mNumVertices;
            ourMesh->vertex = new float[ourMesh->num_vertex * 3];
            memcpy(ourMesh->vertex, sceneM->mVertices, sizeof(float) * ourMesh->num_vertex * 3);
            App->console->AddLog("New mesh with %d vertices", ourMesh->num_vertex);
            // copy faces
            if (sceneM->HasFaces())
            {
                ourMesh->num_index = sceneM->mNumFaces * 3;
                ourMesh->index = new uint[ourMesh->num_index]; // assume each face is a triangle
                for (uint i = 0; i < sceneM->mNumFaces; ++i)
                {
                    if (sceneM->mFaces[i].mNumIndices != 3)
                    {
                        App->console->AddLog("WARNING, geometry face with != 3 indices!");
                    }
                    else
                    {
                        memcpy(&ourMesh->index[i * 3], sceneM->mFaces[i].mIndices, 3 * sizeof(uint));
                    }
                }
            }


            ourMesh->GenerateBuffer();
        }
        aiReleaseImport(scene);
        vertex.push_back(ourMesh);
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

void Vertex::GenerateBuffer()
{
    // Initialization
     //Vertex
    glGenBuffers(1, &id_vertex);
    glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertex * 3, vertex, GL_STATIC_DRAW);

    //Index
    glGenBuffers(1, &id_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * num_index, index, GL_STATIC_DRAW);

    // Textures
    glGenBuffers(1, &id_tex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_tex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * num_index, tex, GL_STATIC_DRAW);
}


void Vertex::LoadMesh()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);


    glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
    glVertexPointer(3, GL_FLOAT, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, texture_id);
    glTexCoordPointer(2, GL_FLOAT, 0, NULL);

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);

    //Draw Mesh
    glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, NULL);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_TEXTURE_COORD_ARRAY, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    //Disables States
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}


