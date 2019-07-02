
#include "header/SunSystem.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/freeglut.h>
#include <glm/gtc/constants.hpp>

SunSystem::SunSystem(cg::GLSLProgram* prog, cg::GLSLProgram* shProg)
	:model(glm::mat4x4(1.0f))
{
	sun = new Sphere(&program , &sunProgram, &sunProgramShaded, &sunProgramPhong, &sunProgramBlinnPhong, planetStacks, 100);
	axis = new Axis(&program);
	moon = new Sphere(&program , &moonProgram, &moonProgramShaded, &moonProgramPhong, &moonProgramBlinnPhong, planetStacks, 25);
	planet = new Sphere(&program , &planetProgram, &planetProgramShaded, &planetProgramPhong, &planetProgramBlinnPhong, planetStacks, 50);

	objParser = new ObjParser();
	exSun = new Mesh(&exSunProgram, &exSunFlat , &exSunGouraud, &exSunPhong, &exSunBlinnPhong);
	objParser->parseObj("lamp.obj", *exSun);

	schiffParser = new ObjParser();
	schiff = new Mesh(&schiffProgram, &schiffFlat, &schiffGouraud, &schiffPhong, &schiffBlinnPhong);
	schiffParser->parseObj("Waluigi.obj", *schiff);
}

SunSystem::~SunSystem()
{
	delete sun;
	delete axis;
	delete planet;
	delete moon;

	delete exSun;
	delete objParser;
	delete schiff;
	delete schiffParser;
}

void SunSystem::init(glm::vec3 eye) {
	sun->setColor(YELLOW);
	sun->init();
	planet->setColor(EMERALD);
	planet->init();
	moon->setColor(WHITE);
	moon->init();
	
	axis->init();

	exSun->setColor(PURPLE);
	exSun->makeDrawable();

	//schiff->scale(0.05);
	schiff->setColor(SILVER);
	schiff->makeDrawable();

	glm::vec4 eyeVec4 = glm::vec4(eye[0], eye[1], eye[2], 1.0f);
	sun->setLightVector(eyeVec4, lightsource);
	planet->setLightVector(eyeVec4, lightsource);
	moon->setLightVector(eyeVec4, lightsource);
	exSun->setLightVector(eyeVec4, lightsource);
	schiff->setLightVector(eyeVec4, lightsource);

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
	model = glm::scale(model, glm::vec3(scale));

	float rad = alpha * (PI / 180);
	model = glm::rotate(model, rad, zAxis);
	axis->draw(model, view, projection);

	/* Malen der ehemaligen Sonne*/
	matrixStack.push(model);
	exSun->draw(model, view, projection);
	model = matrixStack.top();
	matrixStack.pop();

	matrixStack.push(model);
	rad = rotationAngle * (PI / 180);
	model = glm::rotate(model, direction * rad, yAxis);


	drawPlanetOne();
	drawPlanetTwo();


	rad = 2 * rotationMoonAngle * (PI / 180);
	model = glm::rotate(model, direction * rad, yAxis);
	model = glm::translate(model, { 0.0f, planetOneLift, 0.0f });
	drawSchiff();

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
void SunSystem::drawSchiff(){
	matrixStack.push(model);
	float rad = 90 * (PI / 180);
	model = glm::translate(model, { -1.5f, 0.0f, 0.0f });
	model = glm::rotate(model, direction * rad, yAxis);

	schiff->draw(model, view, projection);
	model = matrixStack.top();
	matrixStack.pop();
}
void SunSystem::drawPlanetOne() {
	/* Zeichnen der Achse von Planet 1 */
	matrixStack.push(model);
	model = glm::translate(model, {3.0f, 0.0f, 0.0f});
	axis->draw(model, view, projection);

	/* Zeichen von Planet 1 mit Rotation um sich selbst */
	matrixStack.push(model);
	float rad = rotationAngle * (PI / 180);
	model = glm::rotate(model, direction * rad, yAxis);
	model = glm::translate(model, { 0.0f, planetOneLift, 0.0f });
	planet->draw(model, view, projection);
	model = matrixStack.top();
	matrixStack.pop();
		
	/* Zeichen der Monde mit Rotation um Planet 1 (doppelt so schnelle Rotation) */
	matrixStack.push(model);
	rad = rotationMoonAngle * (PI / 180);
	model = glm::rotate(model, direction * rad, yAxis);
	model = glm::translate(model, { 0.0f, planetOneLift, 0.0f });
	drawPlanetOneMoons();
	model = matrixStack.top();
	matrixStack.pop();

	model = matrixStack.top();
	matrixStack.pop();
}
void SunSystem::drawPlanetOneMoons() {
	/* Zeichen der 4 Monde f�r Planet 1 */
	for (int i = 0; i < 4; i++) {
		matrixStack.push(model);
		float rad = (i*90) * (PI / 180);
		model = glm::rotate(model, direction * rad, yAxis);
		model = glm::translate(model, { 1.0f, 0.0f, 0.0f });
		moon->draw(model, view, projection);
		model = matrixStack.top();
		matrixStack.pop();
	}
}
void SunSystem::drawPlanetTwo() {
	matrixStack.push(model);

	model = glm::translate(model, { -5.0f, 0.0f, 0.0f });
	float rad = -rotationAngle * direction * (PI / 180);
	model = glm::rotate(model, rad, yAxis);

		/* Zeichne Planet 2 */
		matrixStack.push(model);
		rad = beta * (PI / 180);
		model = glm::rotate(model, rad, zAxis);
		rad = rotationAngle * (PI / 180) *2;
		model = glm::rotate(model, direction * rad, yAxis);
		planet->draw(model, view, projection);
		model = matrixStack.top();
		matrixStack.pop();

		/* Zeichne Achse und Monde von Planet 2 */
		matrixStack.push(model);
		rad = beta * (PI / 180);
		model = glm::rotate(model, rad, zAxis);
		rad = rotationMoonAngle * (PI / 180) *2;
		model = glm::rotate(model, direction * rad, yAxis);
		axis->draw(model, view, projection);
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
		model = glm::rotate(model, direction * rad, yAxis);

		matrixStack.push(model);
		model = glm::translate(model, { 1.0f, 0.0f, 0.0f });

		moon->draw(model, view, projection);

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
		model = glm::rotate(model, direction * rad, yAxis);

		matrixStack.push(model);
		model = glm::translate(model, { 0.0f, 0.0f, 1.0f });

		moon->draw(model, view, projection);

		model = matrixStack.top();
		matrixStack.pop();

		model = matrixStack.top();
		matrixStack.pop();
	}

	model = matrixStack.top();
	matrixStack.pop();
}

void SunSystem::toggleNormals() {
	sun->renderNormals = !sun->renderNormals;
	planet->renderNormals = !planet->renderNormals;
	moon->renderNormals = !moon->renderNormals;
}
void SunSystem::scaleUp() {
	if (scale < 2.0f) {
		scale += 0.1f;
	}
}
void SunSystem::scaleDown() {
	if (scale > 0.2f) {
		scale -= 0.1f;
	}
}

void SunSystem::toggleWireframe() {
	sun->renderWireframe = !sun->renderWireframe;
	planet->renderWireframe = !planet->renderWireframe;
	moon->renderWireframe = !moon->renderWireframe;
}

void SunSystem::toggleLightsource() {
	if (lightsource == L_POINT) {
		lightsource = L_DIRECTION;
	} else {
		lightsource = L_POINT;
	}
}

void SunSystem::toggleShading() {
	sun->toggleShading();
	planet->toggleShading();
	moon->toggleShading();
	exSun->toggleShading();
	schiff->toggleShading();
}
void SunSystem::toggleNormalMode() {
	sun->toggleNormal();
	planet->toggleNormal();
	moon->toggleNormal();
}

void SunSystem::toggleMeshNormals() {
	if (exSun->hasNormals) {
		exSun->renderNormals = !exSun->renderNormals;
		schiff->renderNormals = !schiff->renderNormals;
	}
	else {
		exSun->renderNormals = !exSun->renderNormals;
		schiff->renderNormals = !schiff->renderNormals;
		std::cout << "Das Mesh hat keine Normalen, aber wir haben mal eben welche berechnet!" << std::endl;
	}
}

void SunSystem::toggleMeshFaceNormals() {
	exSun->renderFaceNormals = !exSun->renderFaceNormals;
	schiff->renderFaceNormals = !schiff->renderFaceNormals;
}

void SunSystem::toggleBoundingBox() {
	exSun->renderBoundingBox = !exSun->renderBoundingBox;
	schiff->renderBoundingBox = !schiff->renderBoundingBox;
}

void SunSystem::rotateExSunX() {
	exSun->rotateX();
}
void SunSystem::rotateExSunY() {
	exSun->rotateY();
}
void SunSystem::rotateExSunZ() {
	exSun->rotateZ();
}

void SunSystem::scaleObjUp() {
	if (scaleObj < 0.1) {
		scaleObj += 0.01;
		exSun->scale(scaleObj);
	}

}
void SunSystem::scaleObjDown() {
	if (scaleObj > 0.02) {
		scaleObj -= 0.01;
		exSun->scale(scaleObj);
	}
}
void SunSystem::scaleSchiffUp() {
	if (scaleSchiff < 1) {
		scaleSchiff += 0.01;
		schiff->scale(scaleSchiff);
	}
}
void SunSystem::scaleSchiffDown() {
	if (scaleSchiff > 0.02) {
		scaleSchiff -= 0.01;
		schiff->scale(scaleSchiff);
	}
}
