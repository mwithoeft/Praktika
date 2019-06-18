#pragma once
#include <stack>
#include "GLSLProgram.h"
#include "Sphere.h"
#include "Axis.h"

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
	void toggleSunRotation();
	void toggleNormals();
	void toggleWireframe();
	void toggleLightsource();
	void toggleShading();
	void scaleUp();
	void scaleDown();
	void toggleNormalMode();

private:
	std::stack <glm::mat4x4> matrixStack;
	cg::GLSLProgram program;
	cg::GLSLProgram sunProgram;
	cg::GLSLProgram sunProgramShaded;
	cg::GLSLProgram sunProgramPhong;

	cg::GLSLProgram planetProgram;
	cg::GLSLProgram planetProgramShaded;
	cg::GLSLProgram planetProgramPhong;

	cg::GLSLProgram moonProgram;
	cg::GLSLProgram moonProgramShaded;
	cg::GLSLProgram moonProgramPhong;


	glm::mat4x4 view;
	glm::mat4x4 projection;
	glm::mat4x4 model;

	Sphere *sun;
	Axis* axis;
	Sphere* planet;
	Sphere* moon;

	Lightsource lightsource = L_POINT;

	void drawPlanetOne();
	void drawPlanetOneMoons();

	void drawPlanetTwo();
	void drawPlanetTwoMoons();
	
	const glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	const float PI = 3.141592653589793;

	const int alphaStepSize = 5;
	const int betaStepSize = 3;
	const float planetOneLiftStep = 0.125;
	const float speedStep = 0.05f;
	const int planetStacks = 0;

	bool sunRotation = false;


	int alpha = 0;
	int beta = -45;
	float planetOneLift = 0.0f;
	float speed = 0.0f;
	float rotationAngle = 0.0f;
	float rotationMoonAngle = 0.0f;
	Direction direction = RIGHT;

	float scale = 1.0f;
	unsigned int lightIndex = 0;
	glm::vec4 lights[2] = {
	{ 0.0f,  0.0f, 0.0f, 1.0f },
	{ 0.0f, -1.0f, 0.0f, 0.0f }
	};

};