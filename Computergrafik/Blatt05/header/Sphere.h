#pragma once
#include "GLSLProgram.h"
#include "Object.h"

enum Color { RED, GREEN, BLUE, WHITE, YELLOW, CYAN, MAGENTA };


class Sphere {

public:
	Sphere(cg::GLSLProgram* prog, int s, int r);
	~Sphere();
	void init();
	void draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);

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

	glm::vec3 getColor();
	void setColor(Color color);
	glm::vec3 getNormalsColor();
	void setNormalsColor(Color color);

	bool renderNormals = false;
	bool renderWireframe = false;


private :
	cg::GLSLProgram* program;

	Object objNormals;

	Color color = YELLOW;
	Color normalsColor = CYAN;
	GLuint vao;
	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;
	GLuint normalBuffer;

	GLuint indexCount;


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

	std::vector<glm::vec3> positions2;
	std::vector<glm::vec3> colors2;
	std::vector<GLuint> indices2;
	std::vector<glm::vec3> normals;


	bool initialized = false;
	float normalScale = 0.2f;


	glm::vec3 rotateX(float degree, glm::vec3 vertice);
	glm::vec3 rotateY(float degree, glm::vec3 vertice);
	glm::vec3 rotateZ(float degree, glm::vec3 vertice);
	glm::vec3 mirrorXZ(glm::vec3 vertice);

	void rotateSphereX();
	void rotateSphereY();
	void rotateSphereZ();

	void buildNormalVector();
	void calcPoints();
	void initShader();
	void initShader(cg::GLSLProgram& program, const std::string& vert, const std::string& frag);

	int sumVerticesForN(int n);
	int sumVerticesForNUntil(int n, int limit);
	int calcAmountTriangles(int n);
	glm::vec3 computeNormal(glm::vec3 const&, glm::vec3 const&, glm::vec3 const&);
};