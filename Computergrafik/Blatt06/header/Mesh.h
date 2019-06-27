#pragma once

#include "Vertex.h"
#include "Face.h"
#include "Object.h"
#include "GLSLProgram.h"
#include "BoundingBox.h"

#include <vector>

class Mesh {

public:
	Mesh(cg::GLSLProgram* program);
	~Mesh();

	std::vector<Vertex*> vertices;
	std::vector<Face*> faces;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textures;

	void makeDrawable(); //Quasi das, was vorher das Init war
	void draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);

	bool renderNormals = false;
	bool hasNormals = false;
	bool renderBoundingBox = false;

	void calcBoundingBox();

private:

	std::vector<glm::vec3> drawVertices;
	std::vector<glm::vec3> drawColors;
	std::vector<GLushort> drawIndices;

	cg::GLSLProgram* program;
	Object objMesh;
	Object objNormals;
	Object objBoundingBox;


	std::vector<glm::vec3> normalPositions;
	std::vector<glm::vec3> normalColors;
	std::vector<GLuint> normalIndices;

	std::vector<glm::vec3> boundingBoxPositions;
	std::vector<glm::vec3> boundingBoxColors;
	std::vector<GLuint> boundingBoxIndices;

	BoundingBox* boundingBox;

	float normalScale = 0.2f;

	void initNormals();
	void initBoundingBox();
	void initShader(cg::GLSLProgram& program, const std::string& vert, const std::string& frag);
};