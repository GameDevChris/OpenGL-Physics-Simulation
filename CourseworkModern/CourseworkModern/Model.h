#pragma once
#include "Mesh.h"
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class Model
{
public:
	glm::vec3 position;
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;
	string modelPath;
	Model(string path);

	void Draw(Shader shader);
	void loadModel();

private:

	
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

