#pragma once
#include "GLSLProgram.h"

class Sphere {

public:
	Sphere(cg::GLSLProgram* prog);
	Sphere(cg::GLSLProgram* prog, int s, int r);
	~Sphere();
	void init();
	void draw(glm::mat4x4 mvp);

	int getAngleX();
	int getAngleY();
	int getAngleZ();
	void setAngleX(int angle);
	void setAngleY(int angle);
	void setAngleZ(int angle);
	
	void setAngleChange(int angle);
	int getAngleChange();

	int getStacks();
	void setStacks(int s);

	int getRadius();
	void setRadius(int r);


private :
	cg::GLSLProgram* program;


	GLuint vao;
	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;

	const float PI = 3.141592653589793;

	int stacks = 0;
	int radius = 100;

	int xAngle = 0;
	int yAngle = 0;
	int zAngle = 0;
	int angleChange = 3;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;
	std::vector<GLushort> indices;

	bool initialized = false;


	glm::vec3 rotateX(float degree, glm::vec3 vertice);
	glm::vec3 rotateY(float degree, glm::vec3 vertice);
	glm::vec3 rotateZ(float degree, glm::vec3 vertice);
	glm::vec3 mirrorXZ(glm::vec3 vertice);

	void rotateSphereX();
	void rotateSphereY();
	void rotateSphereZ();

	void Sphere::calcPoints();

	int sumVerticesForN(int n);
	int sumVerticesForNUntil(int n, int limit);
	int calcAmountTriangles(int n);
};