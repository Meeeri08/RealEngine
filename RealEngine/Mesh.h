#include "assimp/include/scene.h"
#include "assimp/include/postprocess.h"
#include "glew/include/glew.h"
#include "assimp/include/cimport.h"

#include <Importer.hpp>  

#include <vector>
#include "glmath.h"

struct Vertex
{
    vec3 meshPos;
    vec2 meshTexCoords;
    vec3 meshNorm;

    Vertex (){}

    Vertex(const vec3& pos, const vec2& tex, const vec3& normal)
    {
        meshPos = pos;
        meshTexCoords = tex;
        meshNorm = normal;

    }

    Vertex(const vec3& pos, const vec2& tex)
    {
        meshPos = pos;
        meshTexCoords = tex;
        meshNorm = vec3(0.0f, 0.0f, 0.0f);

    }


};

class Mesh
{
public:
	Mesh() {};
	~Mesh();

	bool LoadMesh(const std::string& Filename);

	void Render();

private:
    bool InitFromScene(const aiScene* pScene, const std::string& Filename);
    void InitMesh(unsigned int Index, const aiMesh* paiMesh);
    //bool InitMaterials(const aiScene* pScene, const std::string& Filename);
    void Clear();

    #define INVALID_MATERIAL 0xFFFFFFFF


    struct MeshEntry {
        MeshEntry();

        ~MeshEntry();

        bool Init(const std::vector<Vertex>& Vertices,
            const std::vector<unsigned int>& Indices);

        GLuint VB;
        GLuint IB;
        unsigned int NumIndices;
        unsigned int MaterialIndex;
    };

    std::vector<MeshEntry> m_Entries;
   // std::vector<Texture*> m_Textures;
};
