#pragma once

#include "Vertex.h"
#include "Face.h"
#include "Object.h"
#include "Sphere.h"
#include "GLSLProgram.h"
#include "BoundingBox.h"

#include <vector>

class Mesh {

public:
	Mesh(cg::GLSLProgram* program, cg::GLSLProgram* flat, cg::GLSLProgram* gouraud, cg::GLSLProgram* phong, cg::GLSLProgram* blinnphong);
	~Mesh();

	std::vector<Vertex*> vertices;
	std::vector<Face*> faces;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textures;

	void makeDrawable(); //Quasi das, was vorher das Init war
	void draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);

	bool renderNormals = false;
	bool renderFaceNormals = false;

	bool hasNormals = false;
	bool renderBoundingBox = false;
	void initShader();
	void calcBoundingBox(const glm::mat4& model);
	void scale(float value);

	void rotateX();
	void rotateY();
	void rotateZ();
	void setColor(Color c);
	glm::vec3 getColor();
	void setLightVector(const glm::vec4& eye, Lightsource lightsource);

	void toggleShading();

private:

	std::vector<glm::vec3> drawVertices;
	std::vector<glm::vec3> drawColors;
	std::vector<GLushort> drawIndices;

	cg::GLSLProgram* shader;
	cg::GLSLProgram* program;
	cg::GLSLProgram* flat;
	cg::GLSLProgram* gouraud;
	cg::GLSLProgram* phong;
	cg::GLSLProgram* blinnphong;
	Object objMesh;
	Object objNormals;
	Object objFaceNormals;
	Object objBoundingBox;


	std::vector<glm::vec3> normalPositions;
	std::vector<glm::vec3> normalColors;
	std::vector<GLuint> normalIndices;

	std::vector<glm::vec3> faceNormalPositions;
	std::vector<glm::vec3> faceNormalColors;
	std::vector<GLuint> faceNormalIndices;

	std::vector<glm::vec3> boundingBoxPositions;
	std::vector<glm::vec3> boundingBoxColors;
	std::vector<GLuint> boundingBoxIndices;

	BoundingBox* boundingBox;

	Color color = YELLOW;

	float angleChange = 3;

	bool intialized = false;

	float normalScale = 0.2f;
	const float PI = 3.141592653589793;

	float scaleObj = 0.05;

	void initNormals();
	void initBoundingBox(const glm::mat4& model);
	void initShader(cg::GLSLProgram& program, const std::string& vert, const std::string& frag);
	void calcFaceNormals();
	void initFaceNormals();
	void calcNormals();
	void setMaterial();
	glm::vec3 computeNormal(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c);

	struct ColorStr {
		glm::vec3 surfKa;
		glm::vec3 surfKd;
		glm::vec3 surfKs;
		float surfShininess;
	};

	ColorStr colorStr;
	Shading shading;
};