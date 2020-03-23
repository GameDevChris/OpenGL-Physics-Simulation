#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <vector>

#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

using namespace std;

class Mesh
{
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	unsigned int VAO;

	Mesh(vector<Vertex> vert, vector<unsigned int> ind, vector<Texture> tex);
	~Mesh();
	void Draw(Shader shader);

private:
	unsigned int VBO, EBO;
	void setupMesh();
};

