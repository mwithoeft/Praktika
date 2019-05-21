#pragma once
#include "GLSLProgram.h"

class Axis
{
public:
	Axis(cg::GLSLProgram* prog);
	~Axis();
	void init();
	void draw(glm::mat4x4 mvp);

private:
	cg::GLSLProgram* program;

	GLuint vao;
	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;

	float yP1 = -1.5f;
	float yP2 = 1.5f;
};