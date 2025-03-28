#include "model.hpp"

Renderer::Model::Model(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | 
                                                   aiProcess_FlipUVs |
                                                   aiProcess_GenNormals |
                                                   aiProcess_OptimizeMeshes |
                                                   aiProcess_OptimizeGraph |
                                                   aiProcess_CalcTangentSpace);
    
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << "\n";
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}


void Renderer::Model::processNode(aiNode *node, const aiScene *scene)
{
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(processMesh(mesh, scene));			
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Renderer::Mesh Renderer::Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    vertices.reserve(mesh->mNumVertices);

    std::vector<GLuint> indices;
    indices.reserve(mesh->mNumVertices);

    std::shared_ptr<Renderer::Material> material = std::make_shared<Renderer::Material>();

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Renderer::Vertex vertex;

        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        vertex.normal.x = mesh->mNormals[i].x;
        vertex.normal.y = mesh->mNormals[i].y;
        vertex.normal.z = mesh->mNormals[i].z;

        if (mesh->mTextureCoords[0]) {
            vertex.texCoord.x = mesh->mTextureCoords[0][i].x;
            vertex.texCoord.y = mesh->mTextureCoords[0][i].y;
        }
        else
            vertex.texCoord = glm::vec2(0.0f);
        
        vertex.tangent.x = mesh->mTangents[i].x;
        vertex.tangent.y = mesh->mTangents[i].y;
        vertex.tangent.z = mesh->mTangents[i].z;

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

        aiColor3D albedo;
        float roughness, metallic;
        mat->Get(AI_MATKEY_COLOR_DIFFUSE, albedo);
        mat->Get(AI_MATKEY_ROUGHNESS_FACTOR, roughness);
        mat->Get(AI_MATKEY_METALLIC_FACTOR, metallic);

        material->albedo = glm::vec3(albedo.r, albedo.g, albedo.b);
        material->metallicRoughness = glm::vec3(0.0f, roughness, metallic);
        
        if (mat->GetTextureCount(aiTextureType_DIFFUSE) >= 1) {
            aiString str;
            mat->GetTexture(aiTextureType_DIFFUSE, 0, &str);
            material->setAlbedoTexture(directory + '/' + str.C_Str());
            if (mat->GetTextureCount(aiTextureType_GLTF_METALLIC_ROUGHNESS) >= 1) {
                aiString str;
                mat->GetTexture(aiTextureType_GLTF_METALLIC_ROUGHNESS, 0, &str);
                material->setMetallicRoughnessTexture(directory + '/' + str.C_Str());
            }
            if (mat->GetTextureCount(aiTextureType_NORMALS)) {
                aiString str;
                mat->GetTexture(aiTextureType_NORMALS, 0, &str);
                material->setNormalTexture(directory + '/' + str.C_Str());
            }
            if (mat->GetTextureCount(aiTextureType_EMISSIVE) >= 1) {
                aiString str;
                mat->GetTexture(aiTextureType_EMISSIVE, 0, &str);
                material->setEmissionTexture(directory + '/' + str.C_Str());
            }
        }

    }
    
    return Renderer::Mesh(vertices, indices, material);
}

void Renderer::Model::draw(Renderer::Shader& shader) {
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].position = position;
        meshes[i].rotation = rotation;
        meshes[i].size = size;
        meshes[i].draw(shader);
    }
}