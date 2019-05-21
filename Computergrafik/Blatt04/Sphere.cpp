#include "Sphere.h"

Sphere::Sphere(cg::GLSLProgram* prog) : program(prog) {}

Sphere::Sphere(cg::GLSLProgram* prog, int s, int r) : program(prog), stacks(s),	radius(r) {}

Sphere::~Sphere()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteBuffers(1, &colorBuffer);
	glDeleteBuffers(1, &positionBuffer);
}


void Sphere::calcPoints() {

	float angleStep = 90 / (stacks + 1);
	float angleEighth = 90; // degrees

	int indicesEighth = sumVerticesForN(stacks + 2);
	int indicesOffset = 0;

	int verticesCounter = stacks + 2;


	for (int sphereEighth = 0; sphereEighth < 8; sphereEighth++) {
		for (int i = 0; i < verticesCounter; i++) {

			float angleRight = 90 / (float)(verticesCounter - i - 1);

			for (int j = 0; j < verticesCounter - i; j++) {

				glm::vec3 point = { 0.0f, 0.0f, 1.0f * ((float)radius / 100) };
				glm::vec3 rotatedAngle = rotateX(-angleStep * i, point);

				if (verticesCounter - i != 1) {
					rotatedAngle = rotateY(angleRight * j, rotatedAngle);
				}

				float angle = angleEighth * (float)(sphereEighth % 4);
				rotatedAngle = rotateY(angle, rotatedAngle);

				if (sphereEighth >= 4) {
					rotatedAngle = mirrorXZ(rotatedAngle);
				}

				vertices.push_back(rotatedAngle);
				colors.push_back(getColor()); // yellow

				if (i != verticesCounter - 1 && j != verticesCounter - i - 1) {
					int left = indicesOffset + sumVerticesForNUntil(verticesCounter, verticesCounter - i + 1) + j;
					int top = left + (verticesCounter - i);
					int right = left + 1;

					if (sphereEighth >= 4) {
						indices.push_back(top);
						indices.push_back(right);
						indices.push_back(left);
					}
					else {
						indices.push_back(top);
						indices.push_back(left);
						indices.push_back(right);
					}

					if (sphereEighth >= 4) {
						if (i > 0) {
							int bottom = right - (verticesCounter - i + 1);
							indices.push_back(bottom);
							indices.push_back(left);
							indices.push_back(right);
						}
					}
					else {
						if (i > 0) {
							int bottom = right - (verticesCounter - i + 1);
							indices.push_back(right);
							indices.push_back(left);
							indices.push_back(bottom);
						}
					}


				}
			}
		}
		indicesOffset += indicesEighth;
	}


}

void Sphere::init() {

	if (!initialized) {
		calcPoints();
		initialized = true;
	}

	GLuint programId = program->getHandle();
	GLuint pos;


	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);
}

void Sphere::draw(glm::mat4x4 mvp) {
	program->use();
	program->setUniform("mvp", mvp);
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 8 * calcAmountTriangles(stacks) * 3, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void Sphere::setColor(Color c) {
	color = c;
}
glm::vec3 Sphere::getColor() {
	switch (color) {
		case RED: return { 1.0f, 0.0f, 0.0f }; break;
		case GREEN: return { 0.0f, 1.0f, 0.0f }; break;
		case BLUE: return { 0.0f, 0.0f, 1.0f }; break;
		case WHITE: return { 1.0f, 1.0f, 1.0f }; break;
		case YELLOW: return { 1.0f, 1.0f, 0.0f }; break;
		case CYAN: return { 0.0f, 1.0f, 1.0f }; break;
		case MAGENTA: return { 1.0f, 0.0f, 1.0f }; break;
	}
}


/*
 * Rotate a vertice on the X axis
 */
glm::vec3 Sphere::rotateX(float degree, glm::vec3 vertice) {
	degree *= -1;
	float rad = degree * (PI / 180);
	glm::mat3x3 rotationMatrix = { {1, 0, 0}, {0, cos(rad), -sin(rad) }, {0, sin(rad), cos(rad)} };
	return rotationMatrix * vertice;
}

/*
 * Rotate a vertice on the Y axis
 */
glm::vec3 Sphere::rotateY(float degree, glm::vec3 vertice) {
	degree *= -1;
	float rad = degree * (PI / 180);
	glm::mat3x3 rotationMatrix = { {cos(rad), 0, sin(rad)}, {0, 1, 0}, {-sin(rad), 0, cos(rad)} };
	return rotationMatrix * vertice;
}

/*
 * Rotate a vertice on the Z axis
 */
glm::vec3 Sphere::rotateZ(float degree, glm::vec3 vertice) {
	degree *= -1;
	float rad = degree * (PI / 180);
	glm::mat3x3 rotationMatrix = { {cos(rad), -sin(rad), 0}, {sin(rad), cos(rad), 0 }, {0, 0, 1} };
	return rotationMatrix * vertice;
}

/*
 * Mirror a vertice on the XZ-pane
 */
glm::vec3 Sphere::mirrorXZ(glm::vec3 vertice) {
	glm::mat3x3 mirrorMatrix = { {1, 0, 0}, {0, -1, 0}, {0, 0, 1} };
	return mirrorMatrix * vertice;
}

/*
 * Rotate the sphere on the X axis
 */
void Sphere::rotateSphereX() {
	for (int i = 0; i < vertices.size(); i++) {
		float x = vertices[i][0];
		float y = vertices[i][1];
		float z = vertices[i][2];

		vertices[i][0] - x;
		vertices[i][1] - y;
		vertices[i] = rotateX(angleChange, vertices[i]);
		vertices[i][0] + x;
		vertices[i][1] + y;
	}
}

/*
 * Rotate the sphere on the Y axis
 */
void Sphere::rotateSphereY() {
	for (int i = 0; i < vertices.size(); i++) {
		float x = vertices[i][0];
		float y = vertices[i][1];
		float z = vertices[i][2];

		vertices[i][1] - y;
		vertices[i][2] - z;
		vertices[i] = rotateY(angleChange, vertices[i]);
		vertices[i][1] + y;
		vertices[i][2] + z;
	}
}

/*
 * Rotate the sphere on the Z axis
 */
void Sphere::rotateSphereZ() {
	for (int i = 0; i < vertices.size(); i++) {
		float x = vertices[i][0];
		float y = vertices[i][1];
		float z = vertices[i][2];

		vertices[i][0] - x;
		vertices[i][2] - z;
		vertices[i] = rotateZ(angleChange, vertices[i]);
		vertices[i][0] + x;
		vertices[i][2] + z;
	}
}


/*
 * Calc the amount of triangles of one qadrant in recursive way.
 * Example returns are 1 for n=0, 4 for n=1, 9 for n=2, 16 for n=3
 */
int Sphere::calcAmountTriangles(int n) {
	if (n == 0) {
		return 1;
	}
	return calcAmountTriangles(n - 1) + (n * 2 + 1);
}

int Sphere::sumVerticesForN(int n) {
	int sum = 0;
	for (int i = n; i > 0; i--) {
		sum += i;
	}
	return sum;
}

int Sphere::sumVerticesForNUntil(int n, int limit) {
	int sum = 0;
	for (int i = n; i > limit - 1; i--) {
		sum += i;
	}
	return sum;
}

int Sphere::getAngleX() {
	return xAngle;
}
int Sphere::getAngleY() {
	return yAngle;
}
int Sphere::getAngleZ() {
	return zAngle;
}
void Sphere::setAngleX(int angle) {
	xAngle = angle;
	rotateSphereX();
	init();
}
void Sphere::setAngleY(int angle) {
	yAngle = angle;
	rotateSphereY();
	init();
}
void Sphere::setAngleZ(int angle) {
	zAngle = angle;
	rotateSphereZ();
	init();
}
void Sphere::setAngleChange(int angle) {
	angleChange = angle;
}
int Sphere::getAngleChange() {
	return angleChange;
}

int Sphere::getStacks() {
	return stacks;
}
void Sphere::setStacks(int s) {
	stacks = s;
}
int Sphere::getRadius() {
	return radius;
}
void Sphere::setRadius(int r) {
	radius = r;
}

