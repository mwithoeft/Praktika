#pragma once
#include <stack>
#include "GLSLProgram.h"
#include "Sphere.h"
#include "Axis.h"
#include "Mesh.h"
#include "ObjParser.h"

enum Direction {LEFT = -1, RIGHT = 1};

class SunSystem {
public:
	SunSystem(cg::GLSLProgram* prog, cg::GLSLProgram* shProg);
	~SunSystem();
	void init(glm::vec3 eye);
	void draw();

	void setView(glm::mat4x4);
	void setProjection(glm::mat4x4);
	void increaseAlpha();
	void decreaseAlpha();
	void increaseBeta();
	void decreaseBeta();
	void increaseSpeed();
	void decreaseSpeed();
	void liftUpPlanetOne();
	void liftDownPlanetOne();
	void toggleNormals();
	void toggleWireframe();
	void toggleLightsource();
	void toggleShading();
	void toggleBoundingBox();
	void scaleUp();
	void scaleDown();
	void toggleNormalMode();
	void toggleMeshNormals();
	void toggleMeshFaceNormals();
	void scaleSchiffUp();
	void scaleSchiffDown();

	void rotateExSunX();
	void rotateExSunY();
	void rotateExSunZ();

	void scaleObjUp();
	void scaleObjDown();

private:
	std::stack <glm::mat4x4> matrixStack;
	cg::GLSLProgram program;
	cg::GLSLProgram sunProgram;
	cg::GLSLProgram sunProgramShaded;
	cg::GLSLProgram sunProgramPhong;
	cg::GLSLProgram sunProgramBlinnPhong;

	cg::GLSLProgram planetProgram;
	cg::GLSLProgram planetProgramShaded;
	cg::GLSLProgram planetProgramPhong;
	cg::GLSLProgram planetProgramBlinnPhong;

	cg::GLSLProgram moonProgram;
	cg::GLSLProgram moonProgramShaded;
	cg::GLSLProgram moonProgramPhong;
	cg::GLSLProgram moonProgramBlinnPhong;

	cg::GLSLProgram exSunProgram;
	cg::GLSLProgram exSunFlat;
	cg::GLSLProgram exSunGouraud;
	cg::GLSLProgram exSunPhong;
	cg::GLSLProgram exSunBlinnPhong;

	cg::GLSLProgram schiffProgram;
	cg::GLSLProgram schiffFlat;
	cg::GLSLProgram schiffGouraud;
	cg::GLSLProgram schiffPhong;
	cg::GLSLProgram schiffBlinnPhong;


	glm::mat4x4 view;
	glm::mat4x4 projection;
	glm::mat4x4 model;

	Sphere *sun;
	Axis* axis;
	Sphere* planet;
	Sphere* moon;

	ObjParser* objParser;
	ObjParser* schiffParser;
	Mesh* exSun;
	Mesh* schiff;

	Lightsource lightsource = L_POINT;

	void drawPlanetOne();
	void drawPlanetOneMoons();

	void drawPlanetTwo();
	void drawPlanetTwoMoons();

	void drawSchiff();
	
	const glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	const float PI = 3.141592653589793;

	const int alphaStepSize = 5;
	const int betaStepSize = 3;
	const float planetOneLiftStep = 0.125;
	const float speedStep = 0.05f;
	const int planetStacks = 4;


	int alpha = 0;
	int beta = -45;
	float planetOneLift = 0.0f;
	float speed = 0.0f;
	float rotationAngle = 0.0f;
	float rotationMoonAngle = 0.0f;
	Direction direction = RIGHT;


	float scale = 1.0f;
	float scaleExSun = 1.0f;
	float scaleSchiff = 1.0f;
	unsigned int lightIndex = 0;
	glm::vec4 lights[2] = {
	{ 0.0f,  0.0f, 0.0f, 1.0f },
	{ 0.0f, -1.0f, 0.0f, 0.0f }
	};

};