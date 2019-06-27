#pragma once

#include "Vertex.h"
#include "Face.h"
#include "Object.h"
#include "GLSLProgram.h"

#include <vector>

typedef struct BoundingBox {
	float max_x;
	float max_y;
	float max_z;
	float min_x;
	float min_y;
	float min_z;
} BoundingBox;

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

private:

	std::vector<glm::vec3> drawVertices;
	std::vector<glm::vec3> drawColors;
	std::vector<GLushort> drawIndices;

	cg::GLSLProgram* program;
	Object objMesh;
	Object objNormals;

	std::vector<glm::vec3> normalPositions;
	std::vector<glm::vec3> normalColors;
	std::vector<GLuint> normalIndices;

	float normalScale = 0.2f;

	void initNormals();
	void initShader(cg::GLSLProgram& program, const std::string& vert, const std::string& frag);
};