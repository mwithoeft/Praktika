#include "header/Mesh.h"

Mesh::Mesh(cg::GLSLProgram* program) : program(program){
}

Mesh::~Mesh(){
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices.at(i)) {
			delete vertices.at(i);
			vertices.at(i) = nullptr;
		}
	}

	for (int i = 0; i < faces.size(); i++) {
		if (faces.at(i)) {
			delete faces.at(i);
			faces.at(i) = nullptr;
		}
	}
}


void Mesh::makeDrawable() {
	drawColors.clear();
	drawIndices.clear();
	drawVertices.clear();

	for (int i = 0; i < vertices.size(); i++) {
		drawVertices.push_back(vertices.at(i)->position);
		drawColors.push_back({ 1.0f, 1.0f, 0.0f }); //Testfarbe
		std::cout << "V: " << vertices.at(i)->position[0] << " " << vertices.at(i)->position[1] << " " << vertices.at(i)->position[2] << std::endl;
	}
	//Funktioniert nur unter der Vorraussetzung, dass jedes Face bereits trianguliert wurde
	for (int i = 0; i < faces.size(); i++) {
		for (int j = 0; j < faces.at(i)->v.size(); j++) {
			drawIndices.push_back(faces.at(i)->v[j]-1);
			std::cout << "I: " << faces.at(i)->v[j] - 1 << std::endl;
		}
	}

	initShader(*program, "shader/simple.vert", "shader/simple.frag");

	GLuint programId = program->getHandle();
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


	
}

void Mesh::draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) {
	glm::mat4 mv = view * model;
	// Create mvp.
	glm::mat4 mvp = projection * mv;

	program->use();
	program->setUniform("mvp", mvp);


	glBindVertexArray(objMesh.vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objMesh.indexBuffer);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_LINES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
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