#include "SunSystem.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/freeglut.h>s
#include <glm/gtc/constants.hpp>

SunSystem::SunSystem(cg::GLSLProgram* prog)
	: program(prog),
	model(glm::mat4x4(1.0f))
{
	sun = new Sphere(prog, 20, 100);
	axis = new Axis(prog);
	planet = new Sphere(prog, 20, 50);
	moon = new Sphere(prog, 20, 25);

}
SunSystem::~SunSystem()
{
	delete sun;
	delete axis;
	delete planet;
	delete moon;
}

void SunSystem::init() {
	sun->init();
	axis->init();
	planet->setColor(GREEN);
	planet->init();

	moon->setColor(WHITE);
	moon->init();

}
void SunSystem::draw() {
	/* Monde drehen sich doppelt so schnell, um den Unterschied zu sehen */
	rotationAngle = speed + rotationAngle;
	rotationMoonAngle = (2 * speed) + rotationMoonAngle;

	if (rotationAngle > 360.0f) {
		rotationAngle = rotationAngle - 360.0f;
	}
	if (rotationMoonAngle > 360.0f) {
		rotationMoonAngle = rotationMoonAngle - 360.0f;
	}

	matrixStack.push(model);

	float rad = alpha * (PI / 180);
	model = glm::rotate(model, rad, zAxis);
	axis->draw(projection * view * model);

	if (sunRotation) {
		matrixStack.push(model);
		rad = rotationAngle * (PI / 180);
		model = glm::rotate(model, rad, yAxis);
		sun->draw(projection * view * model);
		model = matrixStack.top();
		matrixStack.pop();
	}
	else {
		sun->draw(projection * view * model);
	}

	matrixStack.push(model);
	rad = rotationAngle * (PI / 180);
	model = glm::rotate(model, rad, yAxis);
	drawPlanetOne();
	drawPlanetTwo();
	model = matrixStack.top();
	matrixStack.pop();


	model = matrixStack.top();
	matrixStack.pop();
}

void SunSystem::setProjection(glm::mat4x4 p){
	projection = p;
}
void SunSystem::setView(glm::mat4x4 v) {
	view = v;
}

void SunSystem::increaseAlpha() {
	if (alpha < 360) alpha += alphaStepSize;
}
void SunSystem::decreaseAlpha() {
	if (alpha > 0) alpha -= alphaStepSize;
}
void SunSystem::increaseBeta() {
	if (beta < 360) beta += betaStepSize;
}
void SunSystem::decreaseBeta() {
	if (beta > 0) beta -= betaStepSize;
}
void SunSystem::increaseSpeed() {
	if (speed < 0.40f) speed += speedStep;
}
void SunSystem::decreaseSpeed() {
	if (speed > 0.04f) speed -= speedStep;
}

void SunSystem::liftUpPlanetOne() {
	if (planetOneLift < 1.5) planetOneLift += planetOneLiftStep;
}
void SunSystem::liftDownPlanetOne() {
	if (planetOneLift > -1.5) planetOneLift -= planetOneLiftStep;
}
void SunSystem::toggleSunRotation() {
	sunRotation = !sunRotation;
}
void SunSystem::drawPlanetOne() {
	/* Zeichnen der Achse von Planet 1 */
	matrixStack.push(model);
	model = glm::translate(model, {3.0f, 0.0f, 0.0f});
	axis->draw(projection * view * model);

		/* Zeichen von Planet 1 mit Rotation um sich selbst */
		matrixStack.push(model);
		float rad = rotationAngle * (PI / 180);
		model = glm::rotate(model, rad, yAxis);
		model = glm::translate(model, { 0.0f, planetOneLift, 0.0f });
		planet->draw(projection * view * model);
		model = matrixStack.top();
		matrixStack.pop();
		
		/* Zeichen der Monde mit Rotation um Planet 1 (doppelt so schnelle Rotation) */
		matrixStack.push(model);
		rad = rotationMoonAngle * (PI / 180);
		model = glm::rotate(model, rad, yAxis);
		model = glm::translate(model, { 0.0f, planetOneLift, 0.0f });
		drawPlanetOneMoons();
		model = matrixStack.top();
		matrixStack.pop();

	model = matrixStack.top();
	matrixStack.pop();
}
void SunSystem::drawPlanetOneMoons() {
	/* Zeichen der 4 Monde für Planet 1 */
	for (int i = 0; i < 4; i++) {
		matrixStack.push(model);
		float rad = (i*90) * (PI / 180);
		model = glm::rotate(model, rad, yAxis);
		model = glm::translate(model, { 1.0f, 0.0f, 0.0f });
		moon->draw(projection * view * model);
		model = matrixStack.top();
		matrixStack.pop();
	}
}
void SunSystem::drawPlanetTwo() {
	matrixStack.push(model);

	model = glm::translate(model, { -5.0f, 0.0f, 0.0f });
	float rad = -rotationAngle * (PI / 180);
	model = glm::rotate(model, rad, yAxis);

		/* Zeichne Planet 2 */
		matrixStack.push(model);
		rad = beta * (PI / 180);
		model = glm::rotate(model, rad, zAxis);
		rad = rotationAngle * (PI / 180);
		model = glm::rotate(model, rad, yAxis);
		planet->draw(projection * view * model);
		model = matrixStack.top();
		matrixStack.pop();

		/* Zeichne Achse und Monde von Planet 2 */
		matrixStack.push(model);
		rad = beta * (PI / 180);
		model = glm::rotate(model, rad, zAxis);
		rad = rotationMoonAngle * (PI / 180);
		model = glm::rotate(model, rad, yAxis);
		axis->draw(projection * view * model);
		drawPlanetTwoMoons();
		model = matrixStack.top();
		matrixStack.pop();

	model = matrixStack.top();
	matrixStack.pop();
}
void SunSystem::drawPlanetTwoMoons() {
	matrixStack.push(model);
	model = glm::translate(model, { 0.0f, 1.5f, 0.0f });
	for (int i = 0; i < 2; i++) {
		matrixStack.push(model);
		float rad = (i * 180) * (PI / 180);
		model = glm::rotate(model, rad, yAxis);

		matrixStack.push(model);
		model = glm::translate(model, { 1.0f, 0.0f, 0.0f });

		moon->draw(projection * view * model);

		model = matrixStack.top();
		matrixStack.pop();

		model = matrixStack.top();
		matrixStack.pop();
	}
	model = matrixStack.top();
	matrixStack.pop();


	matrixStack.push(model);
	model = glm::translate(model, { 0.0f, -1.5f, 0.0f });
	for (int i = 0; i < 2; i++) {
		matrixStack.push(model);
		float rad = (i * 180) * (PI / 180);
		model = glm::rotate(model, rad, yAxis);

		matrixStack.push(model);
		model = glm::translate(model, { 0.0f, 0.0f, 1.0f });

		moon->draw(projection * view * model);

		model = matrixStack.top();
		matrixStack.pop();

		model = matrixStack.top();
		matrixStack.pop();
	}

	model = matrixStack.top();
	matrixStack.pop();
}