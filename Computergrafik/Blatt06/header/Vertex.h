#pragma once

#include "glm/glm.hpp"

class Vertex
{
public:

	Vertex();
	~Vertex();

	glm::vec3 position;
	unsigned int id;
};