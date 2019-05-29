#pragma once
#include "GLSLProgram.h"

class Planetensystem
{
public:
	Planetensystem(cg::GLSLProgram* prog);
	~Planetensystem();
	void init();
	void render();
private:
	cg::GLSLProgram* program;
};

