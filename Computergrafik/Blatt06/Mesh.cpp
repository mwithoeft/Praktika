#include "header/Mesh.h"
#include <glm/gtc/matrix_inverse.hpp>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "libs/glm/glm/gtx/rotate_vector.hpp"

Mesh::Mesh(cg::GLSLProgram* program, cg::GLSLProgram* phong) : program(program), phong(phong){
	
	boundingBox = new BoundingBox();
}

Mesh::~Mesh(){
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices.at(i)) {
			delete vertices.at(i);
			vertices.at(i) = nullptr;
		}
	}
	vertices.clear();

	for (int i = 0; i < faces.size(); i++) {
		if (faces.at(i)) {
			delete faces.at(i);
		}
	}
	faces.clear();

	delete boundingBox;
}

void Mesh::initShader() {
	/* Hier muss noch umgeschaltet werden. Eventuell auch nicht aus dem Konstruktor aufrufen, wegen umschalten*/
	//initShader(*program, "shader/shadedGouraud.vert", "shader/shadedGouraud.frag");
	initShader(*program, "shader/simple.vert", "shader/simple.frag");
	initShader(*phong, "shader/shadedPhong.vert", "shader/shadedPhong.frag");
	phong->use();
	phong->setUniform("surfKa", { 0.19225f, 0.19225f, 0.19225 });
	phong->setUniform("surfKd", { 0.50754f, 0.50754f, 0.50754f});
	phong->setUniform("surfKs", { 0.508273, 0.508273f, 0.508273f });
	phong->setUniform("surfShininess", 0.4f);
}

void Mesh::makeDrawable() {
	initShader();

	if (!intialized) {
		for (int i = 0; i < vertices.size(); i++) {
			drawVertices.push_back(vertices.at(i)->position);
			drawColors.push_back({ 0.8f, 0.8f, 0.8f }); //Testfarbe
			//Debug: std::cout << "V: " << vertices.at(i)->position[0] << " " << vertices.at(i)->position[1] << " " << vertices.at(i)->position[2] << std::endl;
		}
		drawColors.push_back({ 0.8f, 0.8f, 0.8f });
		//Funktioniert nur unter der Vorraussetzung, dass jedes Face bereits trianguliert wurde
		for (int i = 0; i < faces.size(); i++) {
			for (int j = 0; j < faces.at(i)->v.size(); j++) {
				drawIndices.push_back(faces.at(i)->v[j]-1);
				//Debug: std::cout << "I: " << faces.at(i)->v[j] - 1 << std::endl;
			}
		}
	}


	initNormals();
	GLuint programId = phong->getHandle();
	GLuint pos;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &objMesh.vao);
	glBindVertexArray(objMesh.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &objMesh.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objMesh.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, drawVertices.size() * sizeof(glm::vec3), drawVertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &objMesh.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objMesh.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, drawColors.size() * sizeof(glm::vec3), drawColors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &objMesh.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objMesh.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawIndices.size() * sizeof(GLushort), drawIndices.data(), GL_STATIC_DRAW);

	// Normal buffer.
	glGenBuffers(1, &objMesh.normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objMesh.normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "normal");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void Mesh::initNormals() {

	if (!intialized) {
		for (int i = 0; i < faces.size(); i++) {
			for (int j = 0; j < faces.at(i)->vn.size(); j++) {
				int k = (faces.at(i)->vn[j] - 1);
				if (k <= 0) continue; // Prüfen, ob es die Normale überhaupt gibt

				glm::vec3 p1 = vertices.at(faces.at(i)->v[j] - 1)->position;
				glm::vec3 p2 = {p1 + normals[k] * normalScale };

				// Reihenfolge wichtig //
				normalIndices.push_back(normalPositions.size());
				normalPositions.push_back(p1);
				normalIndices.push_back(normalPositions.size());
				normalPositions.push_back(p2);

				normalColors.push_back({0.0f, 1.0f, 0.0f});
				normalColors.push_back({ 0.0f, 1.0f, 0.0f });

				hasNormals = true;
			}
		}
		intialized = true;
		calcFaceNormals();
		if (!hasNormals) calcNormals();
	}


	initFaceNormals();

	GLuint programId = program->getHandle();
	GLuint pos;

	// Normal buffer.
	glGenBuffers(1, &objNormals.normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objNormals.normalBuffer);
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
	glBufferData(GL_ARRAY_BUFFER, normalPositions.size() * sizeof(glm::vec3), normalPositions.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Color buffer.
	glGenBuffers(1, &objNormals.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objNormals.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, normalColors.size() * sizeof(glm::vec3), normalColors.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Index buffer.
	objNormals.indexCount = (GLuint)normalIndices.size();

	glGenBuffers(1, &objNormals.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objNormals.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, objNormals.indexCount * sizeof(GLuint), normalIndices.data(), GL_STATIC_DRAW);
}

void Mesh::initFaceNormals() {
	GLuint programId = program->getHandle();
	GLuint pos;

	// Vertex array object.
	glGenVertexArrays(1, &objFaceNormals.vao);
	glBindVertexArray(objFaceNormals.vao);

	// Position buffer.
	glGenBuffers(1, &objFaceNormals.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objFaceNormals.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, faceNormalPositions.size() * sizeof(glm::vec3), faceNormalPositions.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Color buffer.
	glGenBuffers(1, &objFaceNormals.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objFaceNormals.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, faceNormalColors.size() * sizeof(glm::vec3), faceNormalColors.data(), GL_STATIC_DRAW);

	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Index buffer.
	objFaceNormals.indexCount = (GLuint)faceNormalIndices.size();

	glGenBuffers(1, &objFaceNormals.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objFaceNormals.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, objFaceNormals.indexCount * sizeof(GLuint), faceNormalIndices.data(), GL_STATIC_DRAW);
}

void Mesh::initBoundingBox(const glm::mat4& model) {
	calcBoundingBox(model);

	boundingBoxIndices.clear();
	boundingBoxPositions.clear();
	boundingBoxColors.clear();

	//Unten
	boundingBoxPositions.push_back(glm::vec4(boundingBox->min_x, boundingBox->min_y, boundingBox->min_z, 1.0f));
	boundingBoxPositions.push_back(glm::vec4(boundingBox->max_x, boundingBox->min_y, boundingBox->min_z, 1.0f));
	boundingBoxPositions.push_back(glm::vec4(boundingBox->max_x, boundingBox->min_y, boundingBox->max_z, 1.0f));
	boundingBoxPositions.push_back(glm::vec4(boundingBox->min_x, boundingBox->min_y, boundingBox->max_z, 1.0f));
	//Oben
	boundingBoxPositions.push_back(glm::vec4(boundingBox->min_x, boundingBox->max_y, boundingBox->min_z, 1.0f));
	boundingBoxPositions.push_back(glm::vec4(boundingBox->max_x, boundingBox->max_y, boundingBox->min_z, 1.0f));
	boundingBoxPositions.push_back(glm::vec4(boundingBox->max_x, boundingBox->max_y, boundingBox->max_z, 1.0f));
	boundingBoxPositions.push_back(glm::vec4(boundingBox->min_x, boundingBox->max_y, boundingBox->max_z, 1.0f));

	boundingBoxIndices.push_back(0);
	boundingBoxIndices.push_back(1);
	boundingBoxIndices.push_back(3);
	boundingBoxIndices.push_back(2);
	boundingBoxIndices.push_back(0);
	boundingBoxIndices.push_back(3);
	boundingBoxIndices.push_back(1);
	boundingBoxIndices.push_back(2);

	boundingBoxIndices.push_back(0);
	boundingBoxIndices.push_back(4);
	boundingBoxIndices.push_back(3);
	boundingBoxIndices.push_back(7);
	boundingBoxIndices.push_back(1);
	boundingBoxIndices.push_back(5);
	boundingBoxIndices.push_back(2);
	boundingBoxIndices.push_back(6);

	boundingBoxIndices.push_back(4);
	boundingBoxIndices.push_back(5);
	boundingBoxIndices.push_back(7);
	boundingBoxIndices.push_back(6);
	boundingBoxIndices.push_back(4);
	boundingBoxIndices.push_back(7);
	boundingBoxIndices.push_back(5);
	boundingBoxIndices.push_back(6);

	for (int i = 0; i < 8; i++) {
		boundingBoxColors.push_back({ 1.0f, 1.0f, 0.0f });
	}

	GLuint programId = program->getHandle();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &objBoundingBox.vao);
	glBindVertexArray(objBoundingBox.vao);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &objBoundingBox.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objBoundingBox.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, boundingBoxPositions.size() * sizeof(glm::vec3), boundingBoxPositions.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(programId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &objBoundingBox.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, objBoundingBox.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, boundingBoxColors.size() * sizeof(glm::vec3), boundingBoxColors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(programId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Index buffer.
	objBoundingBox.indexCount = (GLuint)boundingBoxIndices.size();

	glGenBuffers(1, &objBoundingBox.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objBoundingBox.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, objBoundingBox.indexCount * sizeof(GLuint), boundingBoxIndices.data(), GL_STATIC_DRAW);
}

void Mesh::draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) {
	glm::mat4 mv = view * model;
	// Create mvp.
	glm::mat4 mvp = projection * mv;
	glm::mat3 nm = glm::inverseTranspose(glm::mat3(model));

	phong->use();
	phong->setUniform("modelviewMatrix", mv);
	phong->setUniform("projectionMatrix", projection);
	phong->setUniform("normalMatrix", nm);
	phong->setUniform("light", glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f));
	phong->setUniform("lightI", float(1.0f));


	glBindVertexArray(objMesh.vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objMesh.indexBuffer);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);

	if (renderNormals) {
		program->use();
		program->setUniform("mvp", mvp);
		glBindVertexArray(objNormals.vao);
		glDrawElements(GL_LINES, objNormals.indexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	if (renderFaceNormals) {
		program->use();
		program->setUniform("mvp", mvp);
		glBindVertexArray(objFaceNormals.vao);
		glDrawElements(GL_LINES, objFaceNormals.indexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	if (renderBoundingBox) {
		initBoundingBox(model);
		program->use();
		program->setUniform("mvp", projection* view);
		glBindVertexArray(objBoundingBox.vao);
		glDrawElements(GL_LINES, objBoundingBox.indexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

}

void Mesh::initShader(cg::GLSLProgram& program, const std::string& vert, const std::string& frag) {
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

void Mesh::calcFaceNormals() {

	std::cout << "Berechne Face Normalen..." << std::endl;

	faceNormalIndices.clear();
	faceNormalPositions.clear();
	faceNormalColors.clear();

	for (int i = 0; i < faces.size(); i++) {
		Face& face = *(faces.at(i));

		glm::vec3 p0 = vertices[face.v[0]-1]->position;
		glm::vec3 p1 = vertices[face.v[1]-1]->position;
		glm::vec3 p2 = vertices[face.v[2]-1]->position;
		glm::vec3 normal = computeNormal(p0, p2, p1);

		face.normal = normal;

		faceNormalIndices.push_back(faceNormalPositions.size());
		faceNormalPositions.push_back(p0);
		faceNormalIndices.push_back(faceNormalPositions.size());
		faceNormalPositions.push_back(p0 + normal * normalScale);

		faceNormalIndices.push_back(faceNormalPositions.size());
		faceNormalPositions.push_back(p1);
		faceNormalIndices.push_back(faceNormalPositions.size());
		faceNormalPositions.push_back(p1 + normal * normalScale);

		faceNormalIndices.push_back(faceNormalPositions.size());
		faceNormalPositions.push_back(p2);
		faceNormalIndices.push_back(faceNormalPositions.size());
		faceNormalPositions.push_back(p2 + normal * normalScale);

		for (int i = 0; i < 6; i++) {
			faceNormalColors.push_back({1.0f, 1.0f, 0.0f});
		}
	}

	std::cout << "Face Normalen berechnet." << std::endl;

}

void Mesh::calcNormals() {
	//Schreibe in jeden Vertex die anliegenden Normalen rein
	for (int i = 0; i < faces.size(); i++) {
		Face& face = *(faces.at(i));
		for (int j = 0; j < face.v.size(); j++) {
			Vertex& v = *(vertices[face.v[j]-1]);
			v.faceNormals.push_back(face.normal);
		}
	}
	//Berechne die Normale an jedem Vertex
	for (int i = 0; i < vertices.size(); i++) {
		Vertex& v = *(vertices[i]);
		glm::vec3 normal = { 0.0f, 0.0f, 0.0f };
		for (int j = 0; j < v.faceNormals.size(); j++) {
			normal = normal + v.faceNormals[j];
		}
		normal = glm::normalize(normal);
		normals.push_back(normal);

		normalIndices.push_back(normalPositions.size());
		normalPositions.push_back(v.position);
		normalIndices.push_back(normalPositions.size());
		normalPositions.push_back(v.position + normal * normalScale);

		normalColors.push_back({ 0.0f, 1.0f, 0.0f });
		normalColors.push_back({ 0.0f, 1.0f, 0.0f });

	}

}

void Mesh::calcBoundingBox(const glm::mat4& model) {
	float max_x = -INFINITY;
	float max_y = -INFINITY;
	float max_z = -INFINITY;
	float min_x = INFINITY;
	float min_y = INFINITY;
	float min_z = INFINITY;

	std::cout << "Berechne BoundingBox..." << std::endl;

	for (int i = 0; i < drawVertices.size(); i++) {
		glm::vec4 p = model * glm::vec4(drawVertices[i], 1.0f);
		if (p.x > max_x) max_x = p.x;
		if (p.y > max_y) max_y = p.y;
		if (p.z > max_z) max_z = p.z;

		if (p.x < min_x) min_x = p.x;
		if (p.y < min_y) min_y = p.y;
		if (p.z < min_z) min_z = p.z;
	}

	std::cout << "Bounding Box berechnet." << std::endl;

	boundingBox->max_x = max_x;
	boundingBox->max_y = max_y;
	boundingBox->max_z = max_z;
	boundingBox->min_x = min_x;
	boundingBox->min_y = min_y;
	boundingBox->min_z = min_z;

	boundingBox->sizeX = max_x - min_x;
	boundingBox->sizeY = max_y - min_y;
	boundingBox->sizeZ = max_z - min_z;

	boundingBox->centerX = (min_x + max_x) / 2;
	boundingBox->centerY = (min_y + max_y) / 2;
	boundingBox->centerZ = (min_z + max_z) / 2;
}

void Mesh::rotateX() {
	for (int i = 0; i < drawVertices.size(); i++) {
		drawVertices[i] = glm::rotateX(drawVertices[i], angleChange * (PI / 180));
	}
	for (int i = 0; i < normalPositions.size(); i++) {
		normalPositions[i] = glm::rotateX(normalPositions[i], angleChange * (PI / 180));
	}
	for (int i = 0; i < faceNormalPositions.size(); i++) {
		faceNormalPositions[i] = glm::rotateX(faceNormalPositions[i], angleChange * (PI / 180));
	}
	for (int i = 0; i < normals.size(); i++) {
		normals[i] = glm::rotateX(normals[i], angleChange * (PI / 180));
	}
}

void Mesh::rotateY() {
	for (int i = 0; i < drawVertices.size(); i++) {
		drawVertices[i] = glm::rotateY(drawVertices[i], angleChange * (PI / 180));
	}
	for (int i = 0; i < normalPositions.size(); i++) {
		normalPositions[i] = glm::rotateY(normalPositions[i], angleChange * (PI / 180));
	}
	for (int i = 0; i < faceNormalPositions.size(); i++) {
		faceNormalPositions[i] = glm::rotateY(faceNormalPositions[i], angleChange * (PI / 180));
	}
	for (int i = 0; i < normals.size(); i++) {
		normals[i] = glm::rotateY(normals[i], angleChange * (PI / 180));
	}
}

void Mesh::rotateZ() {
	for (int i = 0; i < drawVertices.size(); i++) {
		drawVertices[i] = glm::rotateZ(drawVertices[i], angleChange * (PI / 180));
	}
	for (int i = 0; i < normalPositions.size(); i++) {
		normalPositions[i] = glm::rotateZ(normalPositions[i], angleChange * (PI / 180));
	}
	for (int i = 0; i < faceNormalPositions.size(); i++) {
		faceNormalPositions[i] = glm::rotateZ(faceNormalPositions[i], angleChange * (PI / 180));
	}
	for (int i = 0; i < normals.size(); i++) {
		normals[i] = glm::rotateZ(normals[i], angleChange * (PI / 180));
	}
}

glm::vec3 Mesh::computeNormal(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c) {
	return glm::normalize(glm::cross(c - a, b - a));
}