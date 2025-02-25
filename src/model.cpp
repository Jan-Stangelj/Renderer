#include "model.hpp"

Renderer::Model::Model(std::string path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | 
                                                   aiProcess_FlipUVs |
                                                   aiProcess_GenNormals |
                                                   aiProcess_OptimizeMeshes);
    
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
    std::vector<Vertex> vertices;   vertices.reserve(mesh->mNumVertices);
    std::vector<unsigned int> indices;  indices.reserve(mesh->mNumVertices);

    Renderer::Material* material = new Renderer::Material();

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

        //std::cout << albedo.r << albedo.g << albedo.b << std::endl;

        material->setAlbedo(glm::vec3(albedo.r, albedo.g, albedo.b));
        material->setRoughness(roughness);
        material->setMetallic(metallic);
        
        if (mat->GetTextureCount(aiTextureType_DIFFUSE) >= 1) {
            aiString str;
            mat->GetTexture(aiTextureType_DIFFUSE, 0, &str);
            material->setAlbedoTexture(directory + '/' + str.C_Str());
        }
        if (mat->GetTextureCount(aiTextureType_AMBIENT_OCCLUSION) >= 1) {
            aiString str;
            mat->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &str);
            material->setAOTexture(directory + '/' + str.C_Str());
        }
        if (mat->GetTextureCount(aiTextureType_DIFFUSE_ROUGHNESS) >= 1) {
            aiString str;
            mat->GetTexture(aiTextureType_DIFFUSE_ROUGHNESS, 0, &str);
            material->setRoughnessTexture(directory + '/' + str.C_Str());
        }
        if (mat->GetTextureCount(aiTextureType_METALNESS) >= 1) {
            aiString str;
            mat->GetTexture(aiTextureType_METALNESS, 0, &str);
            material->setMetallicTexture(directory + '/' + str.C_Str());
        }
    }
    
    return Renderer::Mesh(vertices, indices, material);
}

void Renderer::Model::draw(Renderer::Shader shader) {
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].draw(shader);
    }
}