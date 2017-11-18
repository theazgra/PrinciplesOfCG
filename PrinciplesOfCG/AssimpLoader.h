#pragma once

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <glm\glm.hpp>
#include "Vertex.h"

struct Material
{
    const char* name;
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 reflective;
    glm::vec4 transparent;
    glm::vec4 specular;
    glm::vec4 emmisive;
};

class AssimpLoader
{
public:
    AssimpLoader();
    ~AssimpLoader();

    static aiScene const* loadScene(const char * file);
    //static std::vector<std::vector<AssimpVertex>> getVertexObjects(aiScene const* aiScene);
    static std::vector<std::vector<AssimpVertex>> getVertexObjects(const char* file);
    static std::vector<Material> getMaterials(aiScene const* aiScene);

    
};

