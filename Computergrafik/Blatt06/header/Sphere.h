#pragma once
#include "GLSLProgram.h"
#include "Object.h"



enum Color { EMERALD, RUBY, RED, GREEN, BLUE, WHITE, YELLOW, CYAN, MAGENTA, SILVER};
enum Shading { FLAT, GOURAUD, PHONG, BLINNPHONG};
enum Lightsource { L_POINT, L_DIRECTION };




class Sphere {

public:
	Sphere(cg::GLSLProgram* prog, cg::GLSLProgram* flat, cg::GLSLProgram* gouraud, cg::GLSLProgram* phong, cg::GLSLProgram* blinnphong, int s, int r);
	~Sphere();
	void init();
	void initMaterial();
	void draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
	void setLightVector(const glm::vec4& v, Lightsource lightsource);
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

	void getColor();
	void setColor(Color color);
	glm::vec3 getColor(Color c);
	void setNormalsColor(Color color);

	bool renderNormals = false;
	bool renderWireframe = false;
	void toggleShading();
	void initShader();
	void toggleNormal();

private :
	cg::GLSLProgram *program;
	cg::GLSLProgram *shader;
	cg::GLSLProgram *programFlat;
	cg::GLSLProgram *programGouraud;
	cg::GLSLProgram *programPhong;
	cg::GLSLProgram* programBlinnPhong;

	//Shading shading = GOURAUD;
	Shading shading = FLAT;

	Object objSphere;
	Object objNormals;

	Color color = YELLOW;
	Color normalsColor = CYAN;


	bool normale = true;

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
	
	void initShader(cg::GLSLProgram& program, const std::string& vert, const std::string& frag);

	int sumVerticesForN(int n);
	int sumVerticesForNUntil(int n, int limit);
	int calcAmountTriangles(int n);
	glm::vec3 computeNormal(glm::vec3 const&, glm::vec3 const&, glm::vec3 const&);

	
	struct ColorStr {
		glm::vec3 surfKa;
		glm::vec3 surfKd;
		glm::vec3 surfKs;
		float surfShininess;
	};

	ColorStr colorStr;
};