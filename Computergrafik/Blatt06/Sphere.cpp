#include "header/Sphere.h"
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>

Sphere::Sphere(cg::GLSLProgram* prog, cg::GLSLProgram* flat, cg::GLSLProgram* gouraud, cg::GLSLProgram* phong, cg::GLSLProgram* blinnphong, int s, int r)
	: program(prog), programFlat(flat), programGouraud(gouraud), programPhong(phong), programBlinnPhong(blinnphong), stacks(s), radius(r) {
	
}

Sphere::~Sphere()
{
}

void Sphere::initShader() {
	/* Hier muss noch umgeschaltet werden. Eventuell auch nicht aus dem Konstruktor aufrufen, wegen umschalten*/
	//initShader(*program, "shader/shadedGouraud.vert", "shader/shadedGouraud.frag");
	initShader(*program, "shader/simple.vert", "shader/simple.frag");
	switch (shading) {
		case FLAT:
			initShader(*programFlat, "shader/shaded.vert", "shader/shaded.frag");
			//initShader(*programFlat, "shader/simple.vert", "shader/simple.frag");
			shader = programFlat;
			break;
		case GOURAUD:
			initShader(*programGouraud, "shader/shadedGouraud.vert", "shader/shadedGouraud.frag" );
			shader = programGouraud;
			break;
		case PHONG:
			initShader(*programPhong, "shader/shadedPhong.vert", "shader/shadedPhong.frag");
			shader = programPhong;
			break;
		case BLINNPHONG:
			initShader(*programBlinnPhong, "shader/shadedBlinnPhong.vert", "shader/shadedBlinnPhong.frag");
			shader = programBlinnPhong;
			break;

	}
}

void Sphere::initMaterial() {
	getColor();
	shader->use();
	shader->setUniform("surfKa", colorStr.surfKa);
	shader->setUniform("surfKd", colorStr.surfKd);
	shader->setUniform("surfKs", colorStr.surfKs);
	shader->setUniform("surfShininess", colorStr.surfShininess);
}

void Sphere::calcPoints() {

	float angleStep = 90 / ((float)stacks + 1);
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
				colors.push_back(getColor(color)); // yellow

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

	buildNormalVector();

}

void Sphere::init() {
	initShader();
	if (shading != FLAT) {
		initMaterial();
	}
	if (!initialized) {
		calcPoints();
		initialized = true;
	}
	buildNormalVector();

	GLuint programId = shader->getHandle();
	GLuint pos;


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (renderWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}



	// Vertex array object.
	glGenVertexArrays(1, &objSphere.vao);
	glBindVertexArray(objSphere.vao);

	// Position buffer.
	glGenBuffers(1, &objSphere.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objSphere.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Index buffer.
	objSphere.indexCount = (GLuint)indices.size();

	glGenBuffers(1, &objSphere.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objSphere.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, objSphere.indexCount * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &objSphere.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objSphere.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Normal buffer.
	glGenBuffers(1, &objSphere.normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objSphere.normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "normal");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableClientState(GL_COLOR_ARRAY);
	
	// Build the normals.
	programId = program->getHandle();
	// Vertex array object.
	glGenVertexArrays(1, &objNormals.vao);
	glBindVertexArray(objNormals.vao);

	// Position buffer.
	glGenBuffers(1, &objNormals.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objNormals.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, positions2.size() * sizeof(glm::vec3), positions2.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Color buffer.
	glGenBuffers(1, &objNormals.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objNormals.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, colors2.size() * sizeof(glm::vec3), colors2.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Index buffer.
	objNormals.indexCount = (GLuint)indices2.size();

	glGenBuffers(1, &objNormals.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objNormals.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, objNormals.indexCount * sizeof(GLuint), indices2.data(), GL_STATIC_DRAW);
}

void Sphere::draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) {
	
	glm::mat4 mv = view * model;
	// Create mvp.
	glm::mat4 mvp = projection * mv;

	// Create normal matrix (nm) from model matrix.
	glm::mat3 nm = glm::inverseTranspose(glm::mat3(model));
	
	shader->use();

	// Dieses kann weg, wenn der Shader importiert ist
	if(shading == FLAT){
		shader->setUniform("mvp", mvp);
		shader->setUniform("nm", nm);
	}
	else {
		/* Hier wird in der Konsole noch ein Fehler ausgegeben, weil die Uniform nicht gefunden wurde, weil der Shader noch nicht drin ist*/
		shader->setUniform("modelviewMatrix", mv);
		shader->setUniform("projectionMatrix", projection);
		shader->setUniform("normalMatrix", nm);
	}

	glBindVertexArray(objSphere.vao);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objSphere.indexBuffer);
	//glBindVertexArray(objSphere.vao);
	glDrawElements(GL_TRIANGLES, 8 * calcAmountTriangles(stacks) * 3, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);

	if (renderNormals) {
		program->use();
		program->setUniform("mvp", mvp);
		glBindVertexArray(objNormals.vao);
		glDrawElements(GL_LINES, objNormals.indexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	
}

void Sphere::setLightVector(const glm::vec4& eye, Lightsource lightsource)
{
	shader->use();
	if (shading == FLAT) {
		if (lightsource) {
			shader->setUniform("lightDirection", glm::vec3(-1.0f, 0.0f, 0.0f));
		}
		else {
			shader->setUniform("lightDirection", (glm::vec3) eye);
		}
	}
	else {
		if (lightsource) {
			shader->setUniform("light",glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f));
		}
		else {
			shader->setUniform("light", eye);
		}
		shader->setUniform("lightI", float(1.0f));
	}
}

void Sphere::buildNormalVector() {
	// Zeichne Normale mit Hilfe des Mittelpunkts
	normals.clear();
	indices2.clear();
	positions2.clear();
	colors2.clear();
	if (normale) {
		for (int i = 0; i < vertices.size(); i++) {
			glm::vec3 p1 = { 0.0f, 0.0f, 0.0f };
			glm::vec3 p2 = vertices[i];

			glm::vec3 normal = { p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2] };
			normal = glm::normalize(normal);
			normals.push_back(normal);

			// Reihenfolge wichtig //
			indices2.push_back(positions2.size());
			positions2.push_back(p2);
			indices2.push_back(positions2.size());
			positions2.push_back(p2 + normal * normalScale);

			colors2.push_back(getColor(normalsColor));
			colors2.push_back(getColor(normalsColor));
		}
	}
	else {

		for (int i = 0; i < indices.size(); i += 3) {
			glm::vec3 p1 = vertices[indices[i]];
			glm::vec3 p2 = vertices[indices[i+1]];
			glm::vec3 p3 = vertices[indices[i+2]];

			/* p2 zuerst, weil die Normalen sonst nach innen zeigen */
			glm::vec3 normal = computeNormal(p2, p1, p3);

			/* Reihenfolge wichtig */
			indices2.push_back(positions2.size());
			positions2.push_back(p1);
			indices2.push_back(positions2.size());
			positions2.push_back(p1 + normal * normalScale);

			indices2.push_back(positions2.size());
			positions2.push_back(p2);
			indices2.push_back(positions2.size());
			positions2.push_back(p2 + normal * normalScale);

			indices2.push_back(positions2.size());
			positions2.push_back(p3);
			indices2.push_back(positions2.size());
			positions2.push_back(p3 + normal * normalScale);

			colors2.push_back(getColor(normalsColor));
			colors2.push_back(getColor(normalsColor));
			colors2.push_back(getColor(normalsColor));
			colors2.push_back(getColor(normalsColor));
			colors2.push_back(getColor(normalsColor));
			colors2.push_back(getColor(normalsColor));
			}
	}
}

void Sphere::setColor(Color c) {
	color = c;
}

void Sphere::getColor() {
	switch (color) {
	case RUBY:
		colorStr.surfKa = glm::vec3{ 0.1745f, 0.01175f, 0.01175f };
		colorStr.surfKd = glm::vec3{ 0.61424f, 0.04136f, 0.04136f };
		colorStr.surfKs = glm::vec3{ 0.727811f, 0.626959f, 0.626959f };
		colorStr.surfShininess = 0.6f;
		break;
	case EMERALD:
		colorStr.surfKa = glm::vec3{ 0.0215f, 0.1745f, 0.0215f };
		colorStr.surfKd = glm::vec3{ 0.07568f, 0.61424f, 0.07568f };
		colorStr.surfKs = glm::vec3{ 0.633f, 0.727811f, 0.633f };
		colorStr.surfShininess = 0.6f;
		break;
	case YELLOW:
		colorStr.surfKa = glm::vec3{ 0.5f, 0.5f, 0.0f };
		colorStr.surfKd = glm::vec3{ 0.5f, 0.5f, 0.0f };
		colorStr.surfKs = glm::vec3{ 0.6f, 0.6f, 0.5f };
		colorStr.surfShininess = 0.32f;
		break;
	case BLUE:
		colorStr.surfKa = glm::vec3{ 0.0f, 0.0f, 0.0f };
		colorStr.surfKd = glm::vec3{ 0.0f, 0.0f, 0.5f };
		colorStr.surfKs = glm::vec3{ 0.6f, 0.6f, 0.7f };
		colorStr.surfShininess = 0.25f;
		break;
	case GREEN:
		colorStr.surfKa = glm::vec3{ 0.0f, 0.0f, 0.0f };
		colorStr.surfKd = glm::vec3{ 0.1f, 0.35f, 0.1f };
		colorStr.surfKs = glm::vec3{ 0.45f, 0.55f, 0.45f };
		colorStr.surfShininess = 32.0f;
		break;
	case WHITE:
		colorStr.surfKa = glm::vec3{ 0.0f, 0.0f, 0.0f };
		colorStr.surfKd = glm::vec3{ 0.55f,0.55f,0.55f };
		colorStr.surfKs = glm::vec3{ 0.70f,0.70f,0.70f };
		colorStr.surfShininess = 32.0f;
		break;
	case CYAN:
		colorStr.surfKa = glm::vec3{ 0.0f,0.1f,0.06f };
		colorStr.surfKd = glm::vec3{ 0.0f,0.50980392f,0.50980392f };
		colorStr.surfKs = glm::vec3{ 0.50196078f,0.50196078f,0.50196078f };
		colorStr.surfShininess = 32.0f;
		break;
	case MAGENTA:
		colorStr.surfKa = glm::vec3{ 0.6f,0.0f,0.3f };
		colorStr.surfKd = glm::vec3{ 0.50980392f,0.50980392f, 0.0f };
		colorStr.surfKs = glm::vec3{ 0.50196078f,0.50196078f,0.50196078f };
		colorStr.surfShininess = 32.0f;
		break;
	case PURPLE:
		colorStr.surfKa = glm::vec3{ 0.29f,0.0f,0.51f };
		colorStr.surfKd = glm::vec3{ 0.50980392f,0.50980392f, 0.0f };
		colorStr.surfKs = glm::vec3{ 0.50196078f,0.50196078f,0.50196078f };
		colorStr.surfShininess = 32.0f;
		break;
	case RED:
		colorStr.surfKa = glm::vec3{ 0.0f,0.0f,0.06f };
		colorStr.surfKd = glm::vec3{ 0.5f,0.0f,0.0f };
		colorStr.surfKs = glm::vec3{ 0.7f,0.6f,0.6f };
		colorStr.surfShininess = 32.0f;
		break;
	case SILVER:
		colorStr.surfKa = glm::vec3{ 0.19225f, 0.19225f, 0.19225 };
		colorStr.surfKd = glm::vec3{ 0.50754f, 0.50754f, 0.50754f };
		colorStr.surfKs = glm::vec3{ 0.508273, 0.508273f, 0.508273f };
		colorStr.surfShininess = 0.4f;
		break;
	}
}

void Sphere::setNormalsColor(Color c) {
	normalsColor = c;
}

glm::vec3 Sphere::getColor(Color c) {
	switch (c) {
	case EMERALD: return { 0.0f, 1.0f, 0.0f }; break;
	case RED: return { 1.0f, 0.0f, 0.0f }; break;
	case GREEN: return { 0.0f, 1.0f, 0.0f }; break;
	case BLUE: return { 0.0f, 0.0f, 1.0f }; break;
	case WHITE: return { 1.0f, 1.0f, 1.0f }; break;
	case YELLOW: return { 1.0f, 1.0f, 0.0f }; break;
	case CYAN: return { 0.0f, 1.0f, 1.0f }; break;
	case MAGENTA: return { 1.0f, 0.0f, 1.0f }; break;
	case SILVER: return{0.75f, 0.75f, 0.75f}; break;
	case PURPLE: return{ 0.29f,0.0f,0.51f }; break;

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

glm::vec3 Sphere::computeNormal (glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c) {
	return glm::normalize(glm::cross(c - a, b - a));
}

void Sphere::initShader(cg::GLSLProgram& program, const std::string& vert, const std::string& frag) {
	if (!program.compileShaderFromFile(vert.c_str(), cg::GLSLShader::VERTEX))
	{
		throw std::runtime_error("COMPILE VERTEX: " + program.log());
	}

	if (!program.compileShaderFromFile(frag.c_str(), cg::GLSLShader::FRAGMENT))
	{
		throw std::runtime_error("COMPILE FRAGMENT: " + program.log());
	}

	if (!program.link())
	{
		throw std::runtime_error("LINK: " + program.log());
	}
}

void Sphere::toggleShading() {
	if (shading == FLAT) {
		shading = GOURAUD;
	}
	else if (shading == GOURAUD) {
		shading = PHONG;
	}
	else if (shading == PHONG) {
		shading = BLINNPHONG;
	}
	else {
		shading = FLAT;
	}
	std::ofstream myfile;
}
void Sphere::toggleNormal() {
	normale = !normale;
}
