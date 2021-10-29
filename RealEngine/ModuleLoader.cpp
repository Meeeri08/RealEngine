#include "glew/include/glew.h"
#include <SDL_opengl.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Globals.h"
#include "Application.h"
#include "ModuleLoader.h"
#include <cmath>

#include "cimport.h"
#include "scene.h"
#include "postprocess.h"


#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH  64



ModuleLoader::ModuleLoader(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleLoader::~ModuleLoader()
{}

// Called before render is available
bool ModuleLoader::Init()
{
    LOG("Creating 3D Renderer context");
    bool ret = true;



    return ret;
}

// PreUpdate: clear buffer
update_status ModuleLoader::PreUpdate(float dt)
{

    // Stream log messages to Debug window
    struct aiLogStream stream;
    stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
    aiAttachLogStream(&stream);

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
    LOG("Destroying 3D Renderer");

    // detach log stream
    aiDetachAllLogStreams();

    return true;
}



void ModuleLoader::Load(const char* path, std::vector<Vertex>& vertex)
{

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



    const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
    if (scene != nullptr && scene->HasMeshes())
    {
        // Use scene->mNumMeshes to iterate on scene->mMeshes array

        vertex.resize(scene->mNumMeshes);
        for (int i = 0; i < scene->mNumMeshes; ++i)
        {
            //
            Vertex& ourMesh = vertex[i];
            aiMesh* sceneM = scene->mMeshes[i];

            // copy vertices
            ourMesh.num_vertex = sceneM->mNumVertices;
            ourMesh.vertex = new float[ourMesh.num_vertex * 3];
            memcpy(ourMesh.vertex, sceneM->mVertices, sizeof(float) * ourMesh.num_vertex * 3);
            LOG("New mesh with %d vertices", ourMesh.num_vertex);

            // copy faces
            if (sceneM->HasFaces())
            {
                ourMesh.num_index = sceneM->mNumFaces * 3;
                ourMesh.index = new uint[ourMesh.num_index]; // assume each face is a triangle
                for (uint i = 0; i < sceneM->mNumFaces; ++i)
                {
                    if (sceneM->mFaces[i].mNumIndices != 3)
                    {
                        LOG("WARNING, geometry face with != 3 indices!");
                    }
                    else
                    {
                        memcpy(&ourMesh.index[i * 3], sceneM->mFaces[i].mIndices, 3 * sizeof(uint));
                    }
                }
            }


            ourMesh.GenerateBuffer();
        }
        aiReleaseImport(scene);
    }
    else
        LOG("Error loading scene %s", path);

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


