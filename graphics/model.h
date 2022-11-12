#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "mesh.h"

using namespace std;


class Model {
public:
	vector<Mesh> meshes;

	Model();
	void init();

	void render(Shader shader);
	void cleanup();
};

#endif