#pragma once
#include "GLSLProgram.h"

class Axis
{
public:
	Axis(cg::GLSLProgram* prog);
	~Axis();
	void init();
	void draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);

private:
	cg::GLSLProgram* program;

	GLuint vao;
	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;

	float yP1 = -1.5f;
	float yP2 = 1.5f;
	void initShader(cg::GLSLProgram& program, const std::string& vert, const std::string& frag);
};