#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"
#include "texture.h"

using namespace glm;
using namespace std;

struct Vertex {
	vec3 pos;
	vec2 texCoord;

	static vector<struct Vertex> genlist(float* vertices, int noVertices);
};
typedef struct Vertex Vertex;

class Mesh {
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	unsigned int VAO;

	vector<Texture> textures;

	Mesh();
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

	void render(Shader shader);
	void cleanup();

private:
	unsigned int VBO, EBO;
	void setup();
};


#endif