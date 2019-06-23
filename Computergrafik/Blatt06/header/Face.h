#pragma once

#include <vector>
#include "glm/glm.hpp"

class Face {
public:
	Face();
	~Face();

	glm::vec3 normal;
	std::vector<unsigned int> v;
	std::vector<unsigned int> vt;
	std::vector<unsigned int> vn;

	unsigned int id;

private:

};