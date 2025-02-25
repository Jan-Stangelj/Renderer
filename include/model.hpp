#pragma once

#include <mesh.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>
#include <iostream>


namespace Renderer {
    class Model {
    public:
        Model(std::string path);

        void draw(Renderer::Shader shader);
    private:
        
        std::vector<Mesh> meshes;
        std::string directory;

        void processNode(aiNode* node, const aiScene* scene);
        Renderer::Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    };
}