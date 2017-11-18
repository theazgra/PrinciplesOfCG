#include "stdafx.h"
#include "AssimpLoader.h"


AssimpLoader::AssimpLoader()
{
}


AssimpLoader::~AssimpLoader()
{
}

aiScene const* AssimpLoader::loadScene(const char * file)
{
    Assimp::Importer importer;

    unsigned int importOptions = 
        aiProcess_Triangulate
        | aiProcess_OptimizeMeshes   
        | aiProcess_JoinIdenticalVertices       
        | aiProcess_Triangulate                
        | aiProcess_CalcTangentSpace;

    const aiScene * loadedScene = importer.ReadFile(file, importOptions);

    if (loadedScene)
    {
        return loadedScene;
    }
    else
    {
        printf("Error during parsing mesh from : %s \n", importer.GetErrorString());
        //throw new std::exception("Error while loading scene from file.");
    }
}


std::vector<std::vector<AssimpVertex>> AssimpLoader::getVertexObjects(const char* file)
{
    Assimp::Importer importer;

    unsigned int importOptions =
        aiProcess_Triangulate
        | aiProcess_OptimizeMeshes
        | aiProcess_JoinIdenticalVertices
        | aiProcess_Triangulate
        | aiProcess_CalcTangentSpace;

    const aiScene * loadedScene = importer.ReadFile(file, importOptions);

    if (!loadedScene)
    {
        printf("Error during parsing mesh from : %s \n", importer.GetErrorString());
        throw new std::exception("Error while loading scene from file.");
    }
    


    std::vector<std::vector<AssimpVertex>> objects;

    if (loadedScene->mNumMeshes == 0)
        return objects;

    for (unsigned int i = 0; i < loadedScene->mNumMeshes; i++)
    {
        std::vector<AssimpVertex> objectVertexes;
        aiMesh* mesh = loadedScene->mMeshes[i];
        
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            AssimpVertex vertex;
            if (mesh->HasPositions())
            {                  
                vertex.Position[0] = mesh->mVertices[i].x;
                vertex.Position[1] = mesh->mVertices[i].y;
                vertex.Position[2] = mesh->mVertices[i].z;
            }

            if (mesh->HasNormals())
            {
                vertex.Normal[0] = mesh->mNormals[i].x;
                vertex.Normal[1] = mesh->mNormals[i].y;
                vertex.Normal[2] = mesh->mNormals[i].z;
            }

            if (mesh->HasTextureCoords(0))
            {
                vertex.UV[0] = mesh->mTextureCoords[0][i].x;
                vertex.UV[1] = mesh->mTextureCoords[0][i].y;
            }

            if (mesh->HasTangentsAndBitangents())
            {
                vertex.Tangent[0] = mesh->mTangents[i].x;
                vertex.Tangent[1] = mesh->mTangents[i].y;
                vertex.Tangent[2] = mesh->mTangents[i].z;
            }
            objectVertexes.push_back(vertex);
        }

        objectVertexes.at(0).hasFaces = mesh->HasFaces();
        if (objectVertexes.at(0).hasFaces)
        {
            std::vector<unsigned int> indices;
            for (unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                indices.push_back(mesh->mFaces[i].mIndices[0]);
                indices.push_back(mesh->mFaces[i].mIndices[1]);
                indices.push_back(mesh->mFaces[i].mIndices[2]);
            }
            objectVertexes.at(0).indices = indices;
        }

        objects.push_back(objectVertexes);
    }

    return objects;
}

std::vector<Material> AssimpLoader::getMaterials(aiScene const * aiScene)
{
    if (!aiScene)
    {
        throw new std::exception("Wrong ai scene!");
    }

    std::vector<Material> materials;

    for (unsigned int i = 0; i < aiScene->mNumMaterials; i++)                     
    {
        Material material;

        const aiMaterial* mat = aiScene->mMaterials[i];
        
        aiString name;
        mat->Get(AI_MATKEY_NAME, name);
        material.name = name.C_Str();
        aiColor4D d;
        
        
        d = aiColor4D(0.0f);
        if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &d))
        {
            material.ambient = glm::vec4(d.r, d.g, d.b, d.a);
        }

        d = aiColor4D(0.0f);
        if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
        {
            material.diffuse = glm::vec4(d.r, d.g, d.b, d.a);
        }

        d = aiColor4D(0.0f);
        if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_EMISSIVE, &d))
        {
            material.emmisive = glm::vec4(d.r, d.g, d.b, d.a);
        }

        d = aiColor4D(0.0f);
        if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_REFLECTIVE, &d))
        {
            material.reflective = glm::vec4(d.r, d.g, d.b, d.a);
        }

        d = aiColor4D(0.0f);
        if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &d))
        {
            material.specular = glm::vec4(d.r, d.g, d.b, d.a);
        }

        d = aiColor4D(0.0f);
        if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_TRANSPARENT, &d))
        {
            material.transparent = glm::vec4(d.r, d.g, d.b, d.a);
        }

        materials.push_back(material);
    }

    return materials;
}
