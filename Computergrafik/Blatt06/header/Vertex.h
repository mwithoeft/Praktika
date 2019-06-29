#pragma once

#include "glm/glm.hpp"
#include <vector>

class Vertex
{
public:

	Vertex();
	~Vertex();

	glm::vec3 position;

	std::vector<glm::vec3> faceNormals;
	unsigned int id;
};