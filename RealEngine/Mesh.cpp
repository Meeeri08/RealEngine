#include "glew/include/glew.h"
#include "Mesh.h"

#include <SDL_opengl.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "ModuleSceneIntro.h"
#include <cmath>

Mesh::Mesh(aiMesh* aiMesh)
{
    mesh = aiMesh;
}

Mesh::~Mesh()
{
    delete mesh;
}

void Mesh::Render()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertex_id);
    glNormalPointer(GL_FLOAT, 0, normal_id);

    glClientActiveTexture(GL_TEXTURE0_ARB);
    glTexCoordPointer(2, GL_FLOAT, 0, tex_id);

    glDrawArrays(GL_TRIANGLES, 0, num_vertex);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

int Mesh::Init()
{
    num_vertex = mesh->mNumFaces * 3;

    vertex_id = new float[mesh->mNumFaces * 3 * 3];
    normal_id = new float[mesh->mNumFaces * 3 * 3];
    tex_id = new float[mesh->mNumFaces * 3 * 2];

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];

        for (int j = 0; j < 3; j++)
        {
            aiVector3D tex = mesh->mTextureCoords[0][face.mIndices[j]];
            memcpy(tex_id, &tex, sizeof(float) * 2);
            tex_id += 2;

            aiVector3D normal = mesh->mNormals[face.mIndices[j]];
            memcpy(normal_id, &normal, sizeof(float) * 3);
            normal_id += 3;

            aiVector3D pos = mesh->mVertices[face.mIndices[j]];
            memcpy(vertex_id, &pos, sizeof(float) * 3);
            vertex_id += 3;
        }
    }

    tex_id -= mesh->mNumFaces * 3 * 2;
    normal_id -= mesh->mNumFaces * 3 * 3;
    vertex_id -= mesh->mNumFaces * 3 * 3;
    return mesh->mNumVertices;
}


